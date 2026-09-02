#include <stdio.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}

void sqr(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        array[i] *= array[i];
}


int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    print_array(a, 10);
    sqr(a, 10);
    print_array(a, 10);
}