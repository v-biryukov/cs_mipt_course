#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int i = 1;
    int fact = 1;

    while (i <= n)
    {
        fact *= i;
        i += 1;
    }

    printf("%i\n", fact);
}
