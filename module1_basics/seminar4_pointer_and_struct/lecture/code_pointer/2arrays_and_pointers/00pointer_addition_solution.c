#include <stdio.h>

int main()
{
    int a[6] = {10, 20, 30, 40, 50, 60};

    int* p = &a[2];

    for (int i = -2; i < 4; ++i)
    {
        *(p + i) += 5;
    }

    for (int i = 0; i < 6; ++i)
    {
        printf("%i ", a[i]);
    }
    printf("\n");
}
