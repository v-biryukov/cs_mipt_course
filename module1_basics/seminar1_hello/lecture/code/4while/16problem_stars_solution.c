#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int i = 1;

    while (i <= n)
    {
        printf("*");
        i += 1;
    }

    printf("\n");
}
