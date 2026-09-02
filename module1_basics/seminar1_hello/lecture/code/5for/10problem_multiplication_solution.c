#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int product = 1;

    for (int i = 1; i <= n; ++i)
    {
        int a;
        scanf("%i", &a);
        product *= a;
    }

    printf("%i\n", product);
}