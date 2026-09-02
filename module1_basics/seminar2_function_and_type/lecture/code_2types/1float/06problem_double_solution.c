#include <stdio.h>

int main()
{
    double a, b;
    scanf("%lf%lf", &a, &b);

    printf("%.20lf\n", a / b);
}