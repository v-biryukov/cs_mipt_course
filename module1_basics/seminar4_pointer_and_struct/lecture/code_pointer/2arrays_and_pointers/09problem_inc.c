#include <stdio.h>



void print_array(int* p, int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", p[i]);
    printf("\n");
}



int main()
{
    int a[6] = {10, 20, 30, 40, 50, 60};
    print_array(a, 6);
}


/*
    Задача:

        Напишите функцию 

            void inc(int* p, int size)

        которая будет принимать массив (на самом деле указатель на первый элемент) и число - размер массива.
        Эта функция должна увеличить все элементы массива на 1.
*/