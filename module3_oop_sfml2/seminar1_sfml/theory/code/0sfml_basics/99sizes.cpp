#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    cout << "Stack sizes of SFML classes:" << endl;
    cout << endl << "Basic classes:" << endl;
    cout << "Size of sf::Vector2f = " << sizeof(sf::Vector2f) << endl;
    cout << "Size of sf::Vector2i = " << sizeof(sf::Vector2i) << endl;
    cout << "Size of sf::Vector2u = " << sizeof(sf::Vector2u) << endl;
    cout << "Size of sf::Color = " << sizeof(sf::Color) << endl;
    cout << "Size of sf::String = " << sizeof(sf::String) << endl;

    cout << endl << "Windows:" << endl;
    cout << "Size of sf::Window = " << sizeof(sf::Window) << endl;
    cout << "Size of sf::RenderWindow = " << sizeof(sf::RenderWindow) << endl;

    cout << endl << "Shapes:" << endl;
    cout << "Size of sf::Shape = " << sizeof(sf::Shape) << endl;
    cout << "Size of sf::CircleShape = " << sizeof(sf::CircleShape) << endl;
    cout << "Size of sf::RectangleShape = " << sizeof(sf::RectangleShape) << endl;
    cout << "Size of sf::ConvexShape = " << sizeof(sf::ConvexShape) << endl;
    cout << "Size of sf::Font = " << sizeof(sf::Font) << endl;
    cout << "Size of sf::Text = " << sizeof(sf::Text) << endl;

    cout << endl << "Time:" << endl;
    cout << "Size of sf::Time = " << sizeof(sf::Time) << endl;
    cout << "Size of sf::Clock = " << sizeof(sf::Clock) << endl;

    cout << endl << "Rects:" << endl;
    cout << "Size of sf::IntRect = " << sizeof(sf::IntRect) << endl;
    cout << "Size of sf::FloatRect = " << sizeof(sf::FloatRect) << endl;

    cout << endl << "Events:" << endl;
    cout << "Size of sf::Event = " << sizeof(sf::Event) << endl;
    cout << "Size of sf::Keyboard = " << sizeof(sf::Keyboard) << endl;
    cout << "Size of sf::Mouse = " << sizeof(sf::Mouse) << endl;
}