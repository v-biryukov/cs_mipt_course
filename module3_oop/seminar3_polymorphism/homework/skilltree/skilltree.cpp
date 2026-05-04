#include "raylib.h"
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <stdexcept>


class TextureManager
{
private:
    std::unordered_map<std::string, Texture2D> mTextures;

public:
    ~TextureManager()
    {
        for (auto& [_, tex] : mTextures)
        {
            UnloadTexture(tex);
        }
    }

    Texture2D& get(const std::string& path)
    {
        if (!mTextures.contains(path))
        {
            Texture2D tex = LoadTexture(path.c_str());
            if (tex.id == 0)
            {
                throw std::runtime_error("Failed to load texture: " + path);
            }
            mTextures[path] = tex;
        }
        return mTextures[path];
    }
};


class Node
{
public:
    enum class State
    {
        Blocked,
        Unblocked,
        Activated
    };

protected:
    Vector2 mPosition;
    State mState { State::Blocked };
    std::vector<std::unique_ptr<Node>> mChildren;

public:
    Node(Vector2 pos)
        : mPosition(pos)
    {
    }

    void addChild(std::unique_ptr<Node> child)
    {
        mChildren.push_back(std::move(child));
    }

    void unblock()
    {
        mState = State::Unblocked;
    }

    void block()
    {
        mState = State::Blocked;
        for (auto& c : mChildren)
        {
            c->block();
        }
    }

    const Vector2& getPosition() const
    {
        return mPosition;
    }

    Node* findClicked(Vector2 p)
    {
        if (contains(p))
        {
            return this;
        }

        for (auto& c : mChildren)
        {
            if (auto* res = c->findClicked(p))
            {
                return res;
            }
        }

        return nullptr;
    }    

    virtual bool contains(Vector2 p) const = 0;
    virtual void onClick() = 0;
    virtual void draw() const = 0;
    
    virtual ~Node() = default;
};


class HitNode : public Node
{
protected:
    float mRadius { 24.f };
    Texture2D* mTexture { nullptr };

public:
    HitNode(Vector2 pos, const std::string& icon, TextureManager& tm)
        : Node(pos)
    {
        mTexture = &tm.get(icon);
    }

    bool contains(Vector2 p) const override
    {
        float dx = p.x - mPosition.x;
        float dy = p.y - mPosition.y;
        return dx * dx + dy * dy <= mRadius * mRadius;
    }

    void onClick() override
    {
        if (mState == State::Blocked)
        {
            return;
        }

        if (mState == State::Unblocked)
        {
            mState = State::Activated;
            for (auto& c : mChildren)
            {
                c->unblock();
            }
        }
        else if (mState == State::Activated)
        {
            mState = State::Unblocked;
            for (auto& c : mChildren)
            {
                c->block();
            }
        }
    }

    Color getColor() const
    {
        switch (mState)
        {
            case State::Blocked:   return {40, 40, 40, 255};
            case State::Unblocked: return {80, 80, 40, 255};
            case State::Activated: return {160, 160, 40, 255};
        }
        return WHITE;
    }

    void draw() const override
    {
        for (const auto& c : mChildren)
        {
            DrawLineEx(mPosition, c->getPosition(), 2.0f, getColor());
            c->draw();
        }

        DrawCircleV(mPosition, mRadius, getColor());

        if (mTexture)
        {
            DrawTextureEx(*mTexture,
                          { mPosition.x - mRadius, mPosition.y - mRadius },
                          0.0f,
                          (mRadius * 2) / mTexture->width,
                          WHITE);
        }
    }
};


std::unique_ptr<Node> createTree(TextureManager& tm)
{
    auto root = std::make_unique<HitNode>(Vector2{400, 500}, "icons/icon_lightning.png", tm);

    auto a = std::make_unique<HitNode>(Vector2{200, 400}, "icons/icon_shuriken.png", tm);
    auto b = std::make_unique<HitNode>(Vector2{400, 400}, "icons/icon_bomb.png", tm);
    auto c = std::make_unique<HitNode>(Vector2{600, 400}, "icons/icon_eye.png", tm);

    a->addChild(std::make_unique<HitNode>(Vector2{100, 200}, "icons/icon_shield.png", tm));
    a->addChild(std::make_unique<HitNode>(Vector2{200, 200}, "icons/icon_sword.png", tm));

    auto deep = std::make_unique<HitNode>(Vector2{600, 200}, "icons/icon_bomb.png", tm);
    deep->addChild(std::make_unique<HitNode>(Vector2{500, 100}, "icons/icon_shuriken.png", tm));

    b->addChild(std::make_unique<HitNode>(Vector2{400, 200}, "icons/icon_hand.png", tm));
    b->addChild(std::make_unique<HitNode>(Vector2{500, 200}, "icons/icon_meteorite.png", tm));
    b->addChild(std::move(deep));

    c->addChild(std::make_unique<HitNode>(Vector2{700, 200}, "icons/icon_eye.png", tm));

    root->addChild(std::move(a));
    root->addChild(std::move(b));
    root->addChild(std::move(c));

    return root;
}


int main()
{
    InitWindow(800, 800, "Skill Tree (raylib)");
    SetTargetFPS(60);

    TextureManager tm;
    auto root = createTree(tm);
    root->unblock();

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (auto* node = root->findClicked(mouse))
            {
                node->onClick();
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        root->draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
