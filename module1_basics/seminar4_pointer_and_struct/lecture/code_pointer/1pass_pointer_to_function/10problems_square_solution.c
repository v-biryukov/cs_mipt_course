#include <stdio.h>

void square(int a, int* p)
{
    *p = a * a;
}


int main()
{
    int a = 15;
    int b;

    square(a, &b);

    printf("%i\n", b);
}

