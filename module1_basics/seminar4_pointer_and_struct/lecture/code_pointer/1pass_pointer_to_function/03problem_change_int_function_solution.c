#include <stdio.h>


void mult2(int* p)
{
    *p *= 2;
}


int main()
{
    int a = 10;

    mult2(&a);

    printf("%i\n", a);
}