/*
    Задача
    
        Напишите функцию void multi(int type, int a, int b), которая, в зависимости от значения аргумента type
        должна делать различные вещи.

            При type == 1, она должна вызывать функцию print_even с аргументами a и b.
    
            При type == 2, она должна вызывать функцию print_n_times с аргументами a и b.

            При type == 2, она должна вызывать функцию print_rectangle с аргументами a и b.

            При ином другом значении type, она должна просто печатать Error!.


        Протестируйте вашу функцию в функции main вот так:

            multi(1, 2, 8);
            multi(2, 2, 8);
            multi(3, 2, 8);
            multi(10, 2, 8);
*/

#include <stdio.h>


void print_even(int a, int b) 
{
    if (a % 2 == 1)
        a += 1;

    for (int i = a; i <= b; i += 2)
        printf("%i ", i);
    
    printf("\n");
}

void print_n_times(int a, int n) 
{
    for (int i = 0; i < n; ++i)
        printf("%i ", a);

    printf("\n");
}

void print_rectangle(int a, int b) 
{
    for (int i = 0; i < a; ++i) 
    {
        for (int j = 0; j < b; ++j)
            printf("*");

        printf("\n");
    }
}






int main()
{
    multi(1, 2, 8);
    multi(2, 2, 8);
    multi(3, 2, 8);
    multi(10, 2, 8);
}