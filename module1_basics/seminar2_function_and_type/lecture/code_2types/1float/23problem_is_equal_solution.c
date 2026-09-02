/*
    Задача:

        Напишите функцию int is_equal(double a, double b, double eps), которая будет сравнивать
        два числа a и b с точностью eps.

        Функция должна возвращать 1 если числа a и b равны с точностью eps и 0 иначе.
        Используйте функцию fabs из библиотеки math.h.

*/

#include <stdio.h>
#include <math.h>

int is_equal(double a, double b, double eps)
{
    return fabs(a - b) < eps;
} 

int main()
{
    printf("%i\n", is_equal(5.0, 5.1, 0.01));
    printf("%i\n", is_equal(5.0, 5.001, 0.01));
}
