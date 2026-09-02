#include <stdio.h>

int main()
{
    int a[10] = {42, 75, 21, 82, 83, 89, 20, 99, 36, 63};

    int sum = 0;
    for (int i = 0; i < 10; ++i)
    {
        sum += a[i];
    }

    printf("%i\n", sum);
}