#include <stdio.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}

void add_array(int a[], int b[], int c[], int size)
{
    for (int i = 0; i < size; ++i)
        c[i] = a[i] + b[i];
}


int main()
{
    int a[5] = {10, 20, 30, 40, 50};
    int b[5] = {5, 4, 3, 2, 1};
    int c[5];

    print_array(a, 5);
    print_array(b, 5);

    add_array(a, b, c, 5);

    print_array(c, 5);
}