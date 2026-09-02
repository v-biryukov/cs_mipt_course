/*
    Задача

        На вход подаётся 3 числа. Вам нужно напечатать Different если все числа различны.
        Если же среди этих чисел есть хотя бы 2 равных числа, то нужно написать Some numbers are equal
*/

#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%i%i%i", &a, &b, &c);

    if (a != b && b != c && c != a)
        printf("Different\n");
    else
        printf("Some numbers are equal\n");

}
