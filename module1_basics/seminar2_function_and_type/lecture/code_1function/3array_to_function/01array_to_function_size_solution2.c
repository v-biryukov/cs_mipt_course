#include <stdio.h>


void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}

int main()
{
    int a[10] = {50, 20, 60, -80, 10, 80, 20, 40, -90, 70};

    print_array(a, 10);
    print_array(a, 4);


    int b[6] = {4, 8, 15, 16, 23, 42};

    print_array(b, 6);
    print_array(b, 3);
}