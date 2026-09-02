#include <stdio.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}

void inc_subarray(int a[], int left, int right)
{
    for (int i = left; i < right; ++i)
        a[i] += 1;
}



int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    print_array(a, 10);

    inc_subarray(a, 2, 6);
    print_array(a, 10);

    inc_subarray(a, 0, 10);
    print_array(a, 10);

    inc_subarray(a, 4, 8);
    print_array(a, 10);

}