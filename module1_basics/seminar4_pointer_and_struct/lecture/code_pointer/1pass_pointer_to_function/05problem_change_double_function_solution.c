#include <stdio.h>


void divide(double* p, double x)
{
    *p /= x;
}

int main()
{
    double a = 5.5;
    double b = 14.5;

    divide(&a, b);

    printf("%lf\n", a);
}