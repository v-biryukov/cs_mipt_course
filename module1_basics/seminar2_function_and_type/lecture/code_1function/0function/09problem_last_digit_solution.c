#include <stdio.h>


int last_digit(int x)
{
    return x % 10;
}

int main()
{
    int a;
    scanf("%i", &a);

    printf("%i\n", last_digit(a));
}