#include <stdio.h>


int main()
{
    int a;
    size_t b;
    char c;
    double d;

    printf("size of a = %zu\n", sizeof(a));
    printf("size of b = %zu\n", sizeof(b));
    printf("size of c = %zu\n", sizeof(c));
    printf("size of d = %zu\n", sizeof(d));


    printf("address of a = %p\n", &a);
    printf("address of b = %p\n", &b);
    printf("address of c = %p\n", &c);
    printf("address of d = %p\n", &d);
}