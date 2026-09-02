/*
    Условный оператор if else

    Операторы if else можно повторять несколько раз
*/

#include <stdio.h>

int main()
{
    int a;
    scanf("%i", &a);

    if (a > 0)
        printf("Positive\n");
    else if (a == 0)
        printf("Zero\n");
    else
        printf("Negative\n");
}



/*
    Задача:

        Напишите программу, которая считывает 2 числа и печатает

            Greater  если первое число больше второго
            Equal    если числа равны
            Less     если первое число меньше второго

        Используйте оператор if else
*/