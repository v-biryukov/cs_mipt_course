#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int i = 1;
    while (i <= n)
    {
        int a;
        scanf("%i", &a);
        printf("%i ", a * a);
        i += 1;
    }
    printf("\n");
}