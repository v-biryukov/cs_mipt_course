#include "raylib.h"
#include <vector>
#include <iostream>

#include "button.hpp"
#include "slider.hpp"
#include "draggable.hpp"

int main()
{
    InitWindow(800, 800, "Widgets");
    SetTargetFPS(60);

    std::vector<Button> buttons;
    buttons.emplace_back(Rectangle{350, 300, 200, 80}, "Cat");
    buttons.emplace_back(Rectangle{200, 450, 100, 80}, "Dog");
    buttons.emplace_back(Rectangle{600, 600, 150, 70}, "Mouse");

    std::vector<Slider> sliders;
    sliders.emplace_back(Vector2{500, 500}, Vector2{200, 10}, Vector2{20, 40});
    sliders.emplace_back(Vector2{300, 100}, Vector2{250, 20}, Vector2{30, 60});

    std::vector<Draggable> draggables;
    draggables.emplace_back(Vector2{550, 100}, Vector2{200, 120}, Color{20, 120, 50, 255});
    draggables.emplace_back(Vector2{50, 550}, Vector2{200, 200}, Color{170, 20, 50, 255});
    draggables.emplace_back(Vector2{50, 200}, Vector2{100, 100}, Color{100, 20, 150, 255});

    while (!WindowShouldClose())
    {
        for (auto& b : buttons)
        {
            if (b.update())
            {
                std::cout << "Button clicked\n";
            }
        }

        for (auto& s : sliders)
        {
            s.update();
        }

        for (auto& d : draggables)
        {
            d.update();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (auto& b : buttons)
            b.draw();

        for (auto& s : sliders)
            s.draw();

        for (auto& d : draggables)
            d.draw();

        EndDrawing();
    }

    CloseWindow();
}
