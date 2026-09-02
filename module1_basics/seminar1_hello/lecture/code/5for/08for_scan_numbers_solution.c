#include <stdio.h>

int main()
{
    int sum = 0;

    for (int i = 1; i <= 7; ++i)
    {
        int a;
        scanf("%i", &a);

        if (a % 2 == 0)
            sum += a;
    }

    printf("%i\n", sum);
}