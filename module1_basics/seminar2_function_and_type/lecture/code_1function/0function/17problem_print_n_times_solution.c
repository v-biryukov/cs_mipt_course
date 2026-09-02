#include <stdio.h>


void print_n_times(int a, int n) 
{
    for (int i = 0; i < n; ++i)
        printf("%i ", a);

    printf("\n");
}

int main()
{
    print_n_times(123, 3);
    print_n_times(7, 6);
    print_n_times(1, 20);
}