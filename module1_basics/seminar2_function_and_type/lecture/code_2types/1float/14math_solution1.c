#include <stdio.h>
#include <math.h>


int main()
{
    double a, b;
    scanf("%lf%lf", &a, &b);

    printf("%.3lf\n", sqrt(a * a + b * b));
}