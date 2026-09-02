#include <stdio.h>
#include <math.h>


int main()
{
    const double pi = 3.141592653589793; 

    double h;
    scanf("%lf", &h);

    double angle;
    scanf("%lf", &angle);

    printf("%.3lf %.3lf\n", h * sin(angle * pi / 180), h * cos(angle * pi / 180));
}