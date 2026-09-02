#include <stdio.h>


int main()
{
    double a = 10;
    double b = 20;
    double c = 30;


    printf("%p\n", &a);
    printf("%p\n", &b);
    printf("%p\n", &c);


    printf("%llu\n", &a);
    printf("%llu\n", &b);
    printf("%llu\n", &c);
}
