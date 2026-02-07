#include "SFML/Graphics.hpp"
#include <random>
#include <concepts>
#include "button.hpp"



float getRandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> d(min, max);
    return d(gen);
}

sf::Color getRandomColor()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<sf::Uint8> d;
    return sf::Color(d(gen), d(gen), d(gen));
}


class ShapePool
{
private:

    sf::RectangleShape mField;
    std::vector<sf::Shape*> mShapes;
    sf::RenderWindow& mRenderWindow;

public:

    ShapePool(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size)
    : mRenderWindow(window)
    {
        mField.setPosition(position);
        mField.setSize(size);
        mField.setFillColor(sf::Color(0, 100, 200, 40));
    }

    template<typename Shape>
    void addShape(Shape* p)
    {
        p->setOrigin(p->getGlobalBounds().getSize() / 2.0f);

        sf::Vector2f min = p->getGlobalBounds().getSize() / 2.0f;
        sf::Vector2f max = mField.getSize() - p->getGlobalBounds().getSize() / 2.0f;
        p->setPosition(mField.getPosition() + sf::Vector2f(getRandomFloat(min.x, max.x), getRandomFloat(min.x, max.y)));
        p->setFillColor(getRandomColor());
        mShapes.push_back(p);
    }

    size_t getNumbeorOfShapes() const {return mShapes.size();}
    sf::Vector2f getPosition() const {return mField.getPosition();}
    sf::Vector2f getSize() const {return mField.getSize();}

    sf::Shape& getShape(int index)
    {
        return *mShapes.at(index);
    }


    void draw() const
    {
        for (auto p : mShapes)
            mRenderWindow.draw(*p);
        mRenderWindow.draw(mField);        
    }

    ~ShapePool()
    {
        for (auto* p : mShapes)
            delete p;
    }

};


class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};


class NoCommand : public Command
{
public:
    void execute() override {};
};


class RotateCommand : public Command
{
private:
    ShapePool& mPool;
    size_t mIndex;
    float mAngle;

public:
    RotateCommand(ShapePool& pool, size_t index, float angle) 
    : mPool(pool), mIndex(index), mAngle(angle) {}

    void execute() override
    {
        mPool.getShape(mIndex).rotate(mAngle);
    }
};

class RandomColorCommand : public Command
{
private:
    ShapePool& mPool;
    size_t mIndex;

public:
    RandomColorCommand(ShapePool& pool, size_t index) 
    : mPool(pool), mIndex(index) {}

    void execute() override
    {
        mPool.getShape(mIndex).setFillColor(getRandomColor());
    }
};

class RandomAllColorsCommand : public Command
{
private:
    ShapePool& mPool;
    size_t mIndex;

public:
    RandomAllColorsCommand(ShapePool& pool) 
    : mPool(pool) {}

    void execute() override
    {
        for (size_t i = 0; i < mPool.getNumbeorOfShapes(); ++i)
            mPool.getShape(i).setFillColor(getRandomColor());
    }
};


class RandomAllPositionsCommand : public Command
{
private:
    ShapePool& mPool;

public:
    RandomAllPositionsCommand(ShapePool& pool) 
    : mPool(pool) {}

    void execute() override
    {
        for (size_t i = 0; i < mPool.getNumbeorOfShapes(); ++i)
        {
            sf::Shape& shape = mPool.getShape(i);

            sf::Vector2f min = shape.getGlobalBounds().getSize() / 2.0f;
            sf::Vector2f max = mPool.getSize() - shape.getGlobalBounds().getSize() / 2.0f;
            shape.setPosition(mPool.getPosition() + sf::Vector2f(getRandomFloat(min.x, max.x), getRandomFloat(min.x, max.y)));
        }
    }
};




class ControlPanel
{
private:

    std::vector<Button*> mButtons;
    std::vector<Command*> mCommands;

    sf::RenderWindow& mRenderWindow;

public:

    ControlPanel(sf::RenderWindow& window) : mRenderWindow(window)
    {}

    void addButton(Button* p)
    {
        mButtons.push_back(p);
        mCommands.push_back(new NoCommand);
    }

    void addButton(Button* pb, Command* pc)
    {
        mButtons.push_back(pb);
        mCommands.push_back(pc);
    }

    size_t getNumberOfButtons() const {return mButtons.size();}

    void draw()
    {
        for (auto p : mButtons)
            p->draw();
    }

    void handleEvent(sf::Event event)
    {
        for (std::size_t i = 0; i < mButtons.size(); ++i)
        {
            bool result = mButtons.at(i)->handleEvent(event);
            if (result)
                mCommands.at(i)->execute();
        }
    }

    ~ControlPanel()
    {
        for (auto p : mButtons)
            delete p;
        for (auto p : mCommands)
            delete p;
    }
};




int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Shapes and Command", sf::Style::Default, settings);

    ShapePool pool(window, {300, 50}, {450, 700});
    pool.addShape(new sf::RectangleShape({getRandomFloat(50, 150), getRandomFloat(50, 150)}));
    pool.addShape(new sf::RectangleShape({getRandomFloat(50, 150), getRandomFloat(50, 150)}));
    pool.addShape(new sf::CircleShape(getRandomFloat(30, 100), 3));
    pool.addShape(new sf::CircleShape(getRandomFloat(30, 100)));
    pool.addShape(new sf::CircleShape(getRandomFloat(30, 100)));

    ControlPanel control(window);
    control.addButton(new Button(window, {100, 100}, {100, 50}), new RotateCommand(pool, 0, 30));
    control.addButton(new Button(window, {100, 200}, {100, 50}), new RotateCommand(pool, 1, 45));
    control.addButton(new Button(window, {100, 300}, {100, 50}), new RandomColorCommand(pool, 3));
    control.addButton(new Button(window, {100, 400}, {100, 50}), new RandomAllColorsCommand(pool));
    control.addButton(new Button(window, {100, 500}, {100, 50}), new RandomAllPositionsCommand(pool));
    control.addButton(new Button(window, {100, 600}, {100, 50}));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            control.handleEvent(event);
        }

        window.clear(sf::Color::Black);
        pool.draw();
        control.draw();
        window.display();
    }
}