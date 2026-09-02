#include <stdio.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}

void mult2(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        array[i] *= 2;
}


int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    print_array(a, 10);
    mult2(a, 10);
    print_array(a, 10);
}