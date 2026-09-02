#include <stdio.h>
#include <math.h>

int main()
{
    double a = 1.5;
    double b = 5.0;
    double c = -9.1;

    double* p = &a;

    // Пишите ваш код ниже

    *p *= *p;


    p = &b;
    *p = sqrt(*p);


    p = &c;
    *p = fabs(*p); 


    // ||||||||||||||||||||

    printf("%lf %lf %lf\n", a, b, c);
}


