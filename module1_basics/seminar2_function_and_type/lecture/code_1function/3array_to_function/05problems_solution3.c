#include <stdio.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}

void add_x(int array[], int size, int x)
{
    for (int i = 0; i < size; ++i)
        array[i] += x;
}


int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    print_array(a, 10);
    add_x(a, 10, 6);
    print_array(a, 10);
}