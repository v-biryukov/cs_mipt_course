#include <stdio.h>


int main()
{
    int a = 10;
    int b = 20;
    printf("a: %i\n", a);
    printf("b: %i\n", b);
    printf("Address of a: %p\n", &a);
    printf("Address of b: %p\n", &b);

    int* p = &a;

    printf(" p = %p\n",  p);
    printf("*p = %i\n", *p);

    // |||||||| Пишите код ниже ||||||||

    int** q = &p;

    *q = &b;

    // ||||||||||||||||||||

    printf(" p = %p\n",  p);
    printf("*p = %i\n", *p);
}