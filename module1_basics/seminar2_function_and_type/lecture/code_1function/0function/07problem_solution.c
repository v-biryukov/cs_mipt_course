#include <stdio.h>

int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;

    return result;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int main()
{
    int a, b;
    scanf("%i%i", &a, &b);

    printf("%i\n", factorial(max(a, b)));
}