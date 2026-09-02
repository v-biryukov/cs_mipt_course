#include <stdio.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);

    printf("\n");
}

void set_arithmetic(int a, int d, int n, int result[])
{
    for (int i = 0; i < n; ++i)
    {
        result[i] = a;
        a += d;
    }
}


int main()
{
    int a[50];

    set_arithmetic(100, 6, 10, a);
    print_array(a, 10);


    set_arithmetic(100, -12, 10, a);
    print_array(a, 10);
}