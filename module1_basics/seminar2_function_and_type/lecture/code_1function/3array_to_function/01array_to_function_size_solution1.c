#include <stdio.h>


int max(int array[], int size)
{
    int result = array[0];

    for (int i = 1; i < size; ++i)
    {
        if (array[i] > result)
            result = array[i];
    }

    return result;
}


int main()
{
    int a[10] = {50, 20, 60, -80, 10, 80, 20, 40, -90, 70};

    printf("%i\n", max(a, 10));
    printf("%i\n", max(a, 4));
    printf("%i\n", max(a, 2));
}