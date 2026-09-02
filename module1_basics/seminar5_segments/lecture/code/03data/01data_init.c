/*
    Инициализация в сегменте памяти Данные (Data)

    Инициализация переменных в сегменте данные.
    В отличии от сегментов стек и куча, в сегменте данные переменные всегда инициализируются нулями.
*/

#include <stdio.h>
#include <stdlib.h>

void print_array(int* array, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%i ", array[i]);
    printf("\n\n");
}

int array_data[100];


int main()
{
    int array_stack[100];
    int* array_heap = (int*)malloc(sizeof(int) * 100);


    printf("Array in stack:\n");
    print_array(array_stack, 100);

    printf("Array in heap:\n");
    print_array(array_heap, 100);

    printf("Array in data:\n");
    print_array(array_data, 100);
    
}