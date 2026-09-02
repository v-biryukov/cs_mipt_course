#include <stdlib.h>
#include <stdio.h>

int main()
{
    short* p = (short*)malloc(sizeof(short) * 3);

    p[0] = 100;
    p[1] = 200;
    p[2] = 300;

    for (size_t i = 0; i < 3; ++i)
        printf("%i ", p[i]);
    printf("\n");

    free(p);
}