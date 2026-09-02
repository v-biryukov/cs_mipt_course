#include <stdlib.h>
#include <stdio.h>


int* get_arithmetic(int start, int d, int n)
{
    int* p = (int*)malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; ++i)
        p[i] = start + i * d;
    return p;
}


void print_array(int* array, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%i ", array[i]);
    printf("\n");
}


int main()
{
    int* p = get_arithmetic(200, 7, 50);
    print_array(p, 50);
    free(p);
}