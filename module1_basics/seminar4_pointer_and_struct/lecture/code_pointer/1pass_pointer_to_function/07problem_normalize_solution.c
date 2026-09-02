#include <stdio.h>
#include <math.h>

void normalize(double* pa, double* pb)
{
    double norm = sqrt(*pa * *pa + *pb * *pb);
    *pa /= norm;
    *pb /= norm;
}


int main()
{
    double x = 4.0;
    double y = 3.0;

    normalize(&x, &y);

    printf("%lf %lf\n", x, y);
}

