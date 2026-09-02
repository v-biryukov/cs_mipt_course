#include <stdio.h>

int main()
{
    while (1)
    {
        int a;
        scanf("%i", &a);

        if (a < 0)
            break;

        if (a % 2 == 1)
            printf("Odd\n");
        else
            printf("Even\n");
    }
}
