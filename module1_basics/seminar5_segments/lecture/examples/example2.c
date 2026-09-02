#include <stdlib.h>
#include <stdio.h>

int main()
{
    double* p = (double*)malloc(sizeof(double) * 3);

    p[0] = 1.1;
    p[1] = 2.2;
    p[2] = 3.3;

    for (size_t i = 0; i < 3; ++i)
        printf("%lf ", p[i]);
    printf("\n");

    free(p);
}