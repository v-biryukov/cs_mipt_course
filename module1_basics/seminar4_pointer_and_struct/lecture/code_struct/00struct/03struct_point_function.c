/*
    Структуры и функции

    Структуры можно передавать в функции и возвращать из функций также как и обычные переменных. 
    При передаче в функцию происходит полное копирование структуры и функция работает уже с копией структуры.
    При возвращении из функции также происходит копирование.
*/

#include <stdio.h>

struct point
{
    float x;
    float y;
};

void print_point(struct point a) 
{
    printf("(%f, %f)", a.x, a.y);
}

struct point add_points(struct point a, struct point b) 
{
    struct point result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

int main()
{
    struct point a = {2.1, 4.3}, 
    struct point b = {6.7, 8.9};
    struct point c = add_points(a, b);
    print_point(c);
}