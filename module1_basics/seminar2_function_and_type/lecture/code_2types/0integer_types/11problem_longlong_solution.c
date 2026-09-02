#include <stdio.h>

int main()
{
    unsigned long long a, b;
    scanf("%llu%llu", &a, &b);

    unsigned long long c = a + b;
    printf("%llu\n", c);
}