#include <stdio.h>


int power(int a, int n)
{
    int result = 1;

    for (int i = 0; i < n; ++i)
        result *= a;

    return result;
}

int main()
{
    int a, n;
    scanf("%i%i", &a, &n);
    
    printf("%i\n", power(a, n));
}