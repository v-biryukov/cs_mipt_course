#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int i = 1;
    int sum = 0;
    while (i <= n)
    {
        int a;
        scanf("%i", &a);
        sum += a * a;
        i += 1;
    }
    printf("%i\n", sum);
}