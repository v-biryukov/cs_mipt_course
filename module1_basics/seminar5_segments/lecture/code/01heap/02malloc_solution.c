#include <stdlib.h>
#include <stdio.h>

int main()
{
    double* p = (double*)malloc(sizeof(double));

    *p = 12.34;
    printf("%lf\n", *p);

    free(p);
}