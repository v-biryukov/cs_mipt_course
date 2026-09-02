#include <stdio.h>

int main()
{
    int a[10] = {42, 75, 21, 82, 83, 89, 20, 99, 36, 63};

    for (int i = 9; i >= 0; --i)
    {
        printf("%i ", a[i]);
    }
    printf("\n");
}