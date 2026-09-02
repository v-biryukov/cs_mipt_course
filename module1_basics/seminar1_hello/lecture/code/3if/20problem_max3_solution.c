/*
    Задача

        На вход подаётся 3 числа. Вам нужно напечатать наибольшее из этих чисел
*/

#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%i%i%i", &a, &b, &c);

    int m = a;

    if (m < b)
        m = b;

    if (m < c)
        m = c;

    printf("%i\n", m);
}
