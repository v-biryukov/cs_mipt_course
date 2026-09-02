#include <stdio.h>
#include <math.h>


int main()
{
    const double pi = 3.141592653589793; 

    double a, b;
    scanf("%lf %lf", &a, &b);

    if (a > b)
    {
        double temp = a;
        a = b;
        b = temp;
    }

    printf("%.3lf\n", atan(a / b) * 180.0 / pi);
}