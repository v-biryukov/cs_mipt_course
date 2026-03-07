#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main () 
{
    srand(time(0));
    const int windowWidth = 1200;
    const int windowHeight = 900;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Objects");
    window.setFramerateLimit(60);

    // Массив на указатели на фигуры:
    std::vector<sf::Shape*> objects {
        new sf::CircleShape(60),
        new sf::RectangleShape({40, 80}),
        new sf::CircleShape(100),
        new sf::CircleShape(20),
        new sf::RectangleShape({180, 60})
    };

    for (auto p : objects)
        p->setPosition({static_cast<float>(rand() % windowWidth), static_cast<float>(rand() % windowHeight)});

    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) 
                window.close();
        }

        for (auto p : objects)
            window.draw(*p);

        window.display();
    }

    for (auto p : objects)
        delete p;
}


// Задание 1: 
// Измените цвет всех объектов на случайный

// Задание 2: 
// Добавьте в objects указатель на тип sf::ConvexShape
// Создайте пятиугольник

// Задание 3:
// Добавьте в objects - 20 случайных объектов (круги, прямоугольники или многоугольники)
