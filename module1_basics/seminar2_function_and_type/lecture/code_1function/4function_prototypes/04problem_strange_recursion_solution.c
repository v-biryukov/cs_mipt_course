#include <stdio.h>


void funca(int n);
void funcb(int n);


void funca(int n)
{
    if (n <= 0)
        return;

    printf("a: %i\n", n);
    funcb(n - 1);
}


void funcb(int n)
{
    printf("b: %i\n", n);
    funca(n / 2);
}


int main()
{
    funca(5000);
}
