/*
    Задача

        На вход подаётся 2 числа. Вам нужно напечатать наибольшее из этих чисел
*/

#include <stdio.h>

int main()
{
    int a, b;
    scanf("%i%i", &a, &b);

    if (a > b)
        printf("%i\n", a);
    else
        printf("%i\n", b);
}
