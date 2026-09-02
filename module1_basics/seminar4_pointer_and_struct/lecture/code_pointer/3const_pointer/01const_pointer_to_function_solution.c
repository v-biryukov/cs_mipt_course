#include <stdio.h>


int sum(const int* array, size_t n)
{
    int result = 0;

    for (size_t i = 0; i < n; ++i)
        result += array[i];

    return result;
}


int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    printf("Sum of a = %i\n", sum(a, 10));
}
