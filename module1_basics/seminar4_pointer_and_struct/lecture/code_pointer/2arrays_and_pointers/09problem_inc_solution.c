#include <stdio.h>



void print_array(int* p, int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", p[i]);
    printf("\n");
}

void inc(int* p, int size)
{
    for (int i = 0; i < size; ++i)
        p[i] += 1;
}



int main()
{
    int a[6] = {10, 20, 30, 40, 50, 60};

    print_array(a, 6);

    inc(a, 6);

    print_array(a, 6);
}
