#include <stdio.h>
#include <math.h>


double geometric_mean(double a, double b)
{
    return sqrt(a * b);
}

float geometric_mean_f(float a, float b)
{
    return sqrtf(a * b);
}


int main()
{
    printf("%lf\n", geometric_mean(5.0, 10.0));

    printf("%f\n", geometric_mean_f(5.0f, 10.0f));
}