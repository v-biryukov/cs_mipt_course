#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main () 
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Textures");
    window.setFramerateLimit(60);
    // Создаём и открываем текстуру
    sf::Texture t;
    if (!t.loadFromFile("./graphics/moscow.jpg"))
    {
        std::cout << "Can't load image ./graphics/moscow.jpg" << std::endl;
        exit(1);
    }
    // Создаём спрайт (специальный объект, который может быть покрыт текстурой)
    sf::Sprite sprite;
    sprite.setTexture(t);
    // Задаём положение 'окошка' на текстуре для спрайта
    // 100, 100 - координаты верхнего левого угла 'окошка' на текстуре
    // 300, 400 - размеры 'окошка'
    sprite.setTextureRect({100, 100, 300, 400});
    // Задаём положение самого спрайта
    sprite.setPosition({200, 200});

    float time = 0;
    while (window.isOpen()) 
    {
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed) 
                window.close();

        }

        // Как будет изменяться картинка при вызове следующей команды?
        // sprite.setTextureRect({100 + 10*time, 100, 300, 400});

        // Как будет изменяться картинка при вызове следующей команды?
        // sprite.setTextureRect({100, 100, 300 + 10*time, 400});
        window.draw(sprite);
        window.display();
        time += 1.0 / 60;
    }

    return 0;
}


// Задание 1: 
// Загрузите текстуру graphics/items.png и нарисуйте на экране колечко (5 строка, 2 столбец)
// Увеличьте это колечко в 10 раз (.setScale({10, 10}))

// Задание 2: 
// Загрузите текстуру graphics/props.png и нарисуйте на экране дом и 3 дерева
// (текстуру нужно загружать только один раз)

// Задание 3: 
// Загрузите текстуру graphics/skeleton_walk.png и нарисуте первый кадр скелета

// Задание 4:
// Создайте анимацию движения скелета. Для этого меняйте 'окошко' спрайта на текстуре
// каждые несколько кадров (скорость анимации нужно подобрать самим)

// Задание 5: 
// Загрузите текстуру graphics/background.png и нарисуйте её на всей области экрана

// Задание 6: 
// Сделайте так, чтобы скелет ходил по нажатию клавиш
// Для того, чтобы отобразить обратное движение, можно просто в функции setTextureRect
// задать отрицательные числа