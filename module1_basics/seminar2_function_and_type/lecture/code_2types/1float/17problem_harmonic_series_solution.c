#include <stdio.h>
#include <math.h>


double harmonic(int n)
{
    double result = 0.0;

    for (int i = 1; i <= n; ++i)
    {
        result += 1.0 / i;
    }
    return result;
}


int main()
{
    printf("%lf\n", harmonic(1));
    printf("%lf\n", harmonic(2));
    printf("%lf\n", harmonic(4));
    printf("%lf\n", harmonic(10));
    printf("%lf\n", harmonic(100));
    printf("%lf\n", harmonic(1000));
    printf("%lf\n", harmonic(1000000));
}