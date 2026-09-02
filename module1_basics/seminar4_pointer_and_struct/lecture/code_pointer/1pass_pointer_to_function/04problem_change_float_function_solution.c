#include <stdio.h>


void square(float* p)
{
    *p *= *p;
}


int main()
{
    float a = 2.5;

    square(&a);

    printf("%f\n", a);

}