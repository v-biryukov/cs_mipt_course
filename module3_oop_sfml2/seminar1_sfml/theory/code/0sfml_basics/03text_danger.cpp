/*
    Пример ошибочного использования классов sf::Font и sf::Text.

    Метод setFont класса sf::Text принимает объект типа sf::Font по ссылке и сохраняет внутри себя адрес 
    объекта sf::Font. Это сделано так, потому что шрифт может иметь большой размер, и хранить копию шрифта
    внутри каждого объекта текста было бы неразумно.

    В данном примере в функции getText создаётся локальная переменная шрифта. Затем эта переменная передаётся
    объекту текста с помощью метода setFont. В результате текст будет хранить адрес локального объекта шрифта.
    После выхода из функции getText объект font удалится.
    Если попытаться использовать объект текста, хранящий адрес на удалённый объект шрифта, это приведёт
    к неопределённому поведению.
*/


#include <SFML/Graphics.hpp>
#include <iostream>

sf::Text getText(std::string fontFile)
{
    sf::Font font;

    if (!font.loadFromFile(fontFile))
    {
        std::cout << "Error! Can't load font!" << std::endl;
        std::exit(1);
    }
    
    sf::Text text;
    text.setFont(font);
    text.setString(L"Привет");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color(70, 160, 100));
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition({300, 200});
    return text;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Rotating Text (Error)", sf::Style::Default);
    window.setFramerateLimit(60);
    
    sf::Text text = getText("sourceCodePro.ttf");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        text.rotate(0.1f);

        window.clear(sf::Color::Black);
        window.draw(text);

        window.display();
    }
}