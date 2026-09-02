/*
    Задача:

        Напишите программу, которая находит и печатает все простые числа от 2 до 5000


    В качестве помощи в этом файле представлена программа, которая считывает одно число
    и проверяет является ли это число простым.
*/



#include <stdio.h>

int main() 
{
    int a;
    scanf("%i", &a);

    int is_prime = 1;

    for (int i = 2; i * i <= a; ++i)
    {
        if (a % i == 0)
        {
            is_prime = 0;
            break;
        }
    }

    if (is_prime)
        printf("Prime\n");
    else
        printf("Composite\n");
}