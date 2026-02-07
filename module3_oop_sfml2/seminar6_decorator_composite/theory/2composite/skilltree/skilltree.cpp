/*
    Icons from Ken111
    https://www.flaticon.com/ru/packs/game-skill?k=1650700359068

*/

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "sfline.hpp"

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
    sf::Vector2f mPosition{0, 0};
    State mState{State::Blocked};

    std::vector<std::shared_ptr<Node>> mChildren {};
    inline static sf::Color sBlockedColor   {40, 40, 40};
    inline static sf::Color sUnlockedColor  {80, 80, 40};
    inline static sf::Color sActivatedColor {160, 160, 40};


public:
    Node(sf::Vector2f position) : mPosition{position} {}

    void addChild(std::shared_ptr<Node> child)
    {
        mChildren.push_back(child);
    }

    sf::Vector2f getPosition() const {return mPosition;}
    void setPosition(sf::Vector2f position) {mPosition = position;}

    void unblock()
    {
        mState = State::Unblocked;
    }

    void block()
    {
        mState = State::Blocked;
        for (const auto& child : mChildren)
            child->block();
    }

    void onMousePressed(sf::Vector2f mouseCoords)
    {
        if (mState == State::Blocked)
            return;

        if (collisionTest(mouseCoords)) 
        {
            if (mState == State::Unblocked) 
            {
                mState = State::Activated;
                for (const auto& child : mChildren)
                    child->unblock();
            }

            else if (mState == State::Activated)
            {
                mState = State::Unblocked;
                for (const auto& child : mChildren)
                    child->block();
            }
        }

        for (const auto& child : mChildren)
        {
            child->onMousePressed(mouseCoords);
        }
    }

    virtual bool collisionTest(sf::Vector2f mouseCoords) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
};


class HitNode : public Node
{
private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    float mRadius = 24;
    bool mIsActivated = false;

public:

    HitNode(sf::Vector2f position) : Node{position} {}

    virtual sf::String getIconPath() = 0;

    void loadTexture()
    {
        sf::String texturePath = getIconPath();
        if (!mTexture.loadFromFile(texturePath))
        {
            std::cout << "Error! Can't load file " << texturePath.toAnsiString() << std::endl;
            std::exit(1);
        }
        mSprite.setTexture(mTexture);
        mSprite.setOrigin({mRadius, mRadius});
        mSprite.setPosition(mPosition);
    }


    sf::Color getCurrentColor() const
    {
        if (mState == State::Unblocked)
            return sUnlockedColor;
        else if (mState == State::Activated)
            return sActivatedColor;
        return sBlockedColor;
    }

    bool collisionTest(sf::Vector2f mouseCoords) override
    {
        sf::Vector2f d = mPosition - mouseCoords;
        return d.x * d.x + d.y * d.y < mRadius * mRadius;
    }

    void draw(sf::RenderWindow& window) const override
    {
        for (const auto& el : mChildren)
        {
            sfLine connectionLine {mPosition, el->getPosition(), getCurrentColor(), 2};
            connectionLine.draw(window);
            el->draw(window);
        }

        static sf::CircleShape shape(mRadius);
        shape.setOrigin({mRadius, mRadius});
        shape.setFillColor(getCurrentColor());
        shape.setPosition(mPosition);
        window.draw(shape);

        window.draw(mSprite);
    }
};



class BombSkillNode : public HitNode
{
public:
    BombSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_bomb.png"};
    }
};

class SpikesSkillNode : public HitNode
{
public:
    SpikesSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_spikes.png"};
    }
};


class LightningSkillNode : public HitNode
{
public:
    LightningSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_lightning.png"};
    }
};


class EyeSkillNode : public HitNode
{
public:
    EyeSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_eye.png"};
    }
};


class ClawsSkillNode : public HitNode
{
public:
    ClawsSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_claws.png"};
    }
};

class ShieldSkillNode : public HitNode
{
public:
    ShieldSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_shield.png"};
    }
};


class SwordSkillNode : public HitNode
{
public:
    SwordSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_sword.png"};
    }
};


class ShurikenSkillNode : public HitNode
{
public:
    ShurikenSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_shuriken.png"};
    }
};

class WindSkillNode : public HitNode
{
public:
    WindSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_shuriken.png"};
    }
};


class MeteoriteSkillNode : public HitNode
{
public:
    MeteoriteSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_meteorite.png"};
    }
};

class HandSkillNode : public HitNode
{
public:
    HandSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_hand.png"};
    }
};

class EarthquakeSkillNode : public HitNode
{
public:
    EarthquakeSkillNode(sf::Vector2f position) : HitNode{position} 
    {
        loadTexture();
    }

    sf::String getIconPath() override
    {
        return sf::String{"icons/icon_earthquake.png"};
    }
};


std::shared_ptr<Node> createSkillTree()
{
    std::shared_ptr<Node> root  {new LightningSkillNode({400, 500})};
    std::shared_ptr<Node> a     {new ShurikenSkillNode({200, 400})};
    std::shared_ptr<Node> b     {new BombSkillNode({400, 400})};
    std::shared_ptr<Node> c     {new EyeSkillNode({600, 400})};
    root->addChild(a);
    root->addChild(b);
    root->addChild(c);

    a->addChild(std::shared_ptr<Node>{new ShieldSkillNode({100, 200})});
    a->addChild(std::shared_ptr<Node>{new SwordSkillNode({200, 200})});
    a->addChild(std::shared_ptr<Node>{new EarthquakeSkillNode({300, 200})});

    b->addChild(std::shared_ptr<Node>{new HandSkillNode({400, 200})});
    b->addChild(std::shared_ptr<Node>{new MeteoriteSkillNode({500, 200})});
    std::shared_ptr<Node> e {new BombSkillNode({600, 200})};
    b->addChild(e);
    e->addChild(std::shared_ptr<Node>{new WindSkillNode({500, 100})});
    e->addChild(std::shared_ptr<Node>{new SwordSkillNode({600, 100})});
    c->addChild(std::shared_ptr<Node>{new EyeSkillNode({700, 200})});

    return root;
}


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Skill Tree", sf::Style::Close, settings);
    window.setFramerateLimit(60);

    std::shared_ptr<Node> root = createSkillTree();
    root->unblock();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouseCoords = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                root->onMousePressed(mouseCoords);
            }
        }

        window.clear(sf::Color::Black);
        root->draw(window);
        window.display();
    }
}