#include <stdio.h>

int main()
{
    const double pi = 3.141592653589793;

    double r;
    scanf("%lf", &r);

    double volume = 4.0 / 3.0 * pi * r * r * r;
    printf("%lf\n", volume);
}