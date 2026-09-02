#include <stdio.h>


int main()
{
    float a = 1.5f;

    float* p = &a;

    *p += 1;

    printf("%f\n", a);
}