#include <iostream>
#include <cmath>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Вспомогательные функции, вычисляет расстояние между двумя точками
float distance(sf::Vector2f start, sf::Vector2f finish)
{
    return std::sqrt((start.x - finish.x)*(start.x - finish.x) + (start.y - finish.y)*(start.y - finish.y));
}

// Вспомогательные функции, рисует линию на холсте окна window
void drawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f finish, sf::Color color = sf::Color::White)
{
    sf::Vertex line_vertices[2] = {sf::Vertex(start, color), sf::Vertex(finish, color)};
    window.draw(line_vertices, 2, sf::Lines);
}


//  Вспомагательный класс, описывет шарик
//      position - положение шарика; radius - радиус
//      isChoosen - говорит о том, выбран ли шарик или нет
struct Ball
{
    sf::Vector2f position;
    float radius;
    bool isChoosen;

    Ball(sf::Vector2f position, float radius) : position(position), radius(radius)
    {
        isChoosen = false;
    }

    // Метод, который рисует шарик на холст окна window
    void draw(sf::RenderWindow& window) const
    {
        // Тут рисуем белый кружочек
        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color::White);
        circle.setOrigin({radius, radius});
        circle.setPosition(position);
        window.draw(circle);

        // Если шарик выбран
        if (isChoosen) 
        {
            // То рисуем "уголки"
            const float fraction = 0.7;
            drawLine(window, {position.x - radius, position.y + radius}, {position.x - radius, position.y + radius*fraction});
            drawLine(window, {position.x - radius, position.y + radius}, {position.x - fraction * radius, position.y + radius});

            drawLine(window, {position.x + radius, position.y + radius}, {position.x + radius, position.y + radius*fraction});
            drawLine(window, {position.x + radius, position.y + radius}, {position.x + radius*fraction, position.y + radius});

            drawLine(window, {position.x + radius, position.y - radius}, {position.x + radius*fraction, position.y - radius});
            drawLine(window, {position.x + radius, position.y - radius}, {position.x + radius, position.y - radius*fraction});

            drawLine(window, {position.x - radius, position.y - radius}, {position.x - radius*fraction, position.y - radius});
            drawLine(window, {position.x - radius, position.y - radius}, {position.x - radius, position.y - radius*fraction});
        }
    }
};


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Select, Move, Delete!", sf::Style::Default, settings);
    window.setFramerateLimit(60);


    // Создаём связный список из шариков
    // Связный список -- потому что нам нужно будет постоянно удалять и добавлять в этот список
    std::list<Ball> balls;
    balls.push_back(Ball({200, 200}, 26));
    balls.push_back(Ball({400, 300}, 20));
    balls.push_back(Ball({500, 100}, 16));
    balls.push_back(Ball({200, 400}, 18));
    balls.push_back(Ball({350, 150}, 22));
    balls.push_back(Ball({750, 400}, 21));


    // Создаём прямоугольник выделения
    // Обратите внимание на четвёртый параметр FillColor, он равен 50.
    // Это alpha - прозрачность      0 = полностью прозрачный     255 = непрозрачный
    sf::RectangleShape selectionRect;
    selectionRect.setFillColor(sf::Color(150, 150, 240, 50));
    selectionRect.setOutlineColor(sf::Color(200, 200, 255));
    selectionRect.setOutlineThickness(1);

    // Специальная переменная, которая будет показывать, что мы находимся в режиме выделения
    bool isSelecting = false;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            
            if (event.type == sf::Event::MouseMoved) 
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                
                // Если мы находимся в режиме выделения, то меняем прямоугольник выделения
                if (isSelecting)
                    selectionRect.setSize(mousePosition - selectionRect.getPosition());
            }

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    // Если не зажат левый Ctrl, то все выделения снимаются
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    {
                        for (Ball& b : balls)
                            b.isChoosen = false;
                    } 

                    // Проверяем попал ли курсор в какой-нибудь шарик, если попал - выделяем
                    for (Ball& b : balls) 
                    {
                        if (distance(mousePosition, b.position) < b.radius) 
                        {
                            b.isChoosen = true;
                            break;
                        }
                    }

                    // ЛКМ + левый Alt - добавляем новый случайный шарик
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
                        balls.push_back(Ball(mousePosition, 5 + rand() % 40));

                    // Задаём новое положения прямоугольника выделения
                    isSelecting = true;
                    selectionRect.setPosition(mousePosition);
                    selectionRect.setSize({0, 0});
                }
            }

            // При отпускании кнопки мыши выходим из режима выделения
            if (event.type == sf::Event::MouseButtonReleased) 
                isSelecting = false;
        }

        window.clear(sf::Color::Black);

        // Рисуем все шарики
        for (Ball& b : balls)
            b.draw(window);


        // Рисуем прямоугольник выделения
        if (isSelecting)
            window.draw(selectionRect);

        window.display();
    }

    return 0;
}