#include <stdio.h>
#include <math.h>

int main()
{
    const double eps = 1e-15;

    double a = 3 * 0.1;
    double b = 0.3;

    if (fabs(a - b) < eps)
        printf("Yes\n");
    else
        printf("No\n");
}