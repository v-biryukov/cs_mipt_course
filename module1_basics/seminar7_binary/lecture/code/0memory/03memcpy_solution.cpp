#include <stdio.h>
#include <string.h>
#include <math.h>


int main()
{

    float a[100];

    for (size_t i = 0; i < 100; ++i)
    {
        a[i] = sqrtf(i);
    }


    float b[50];

    memcpy(b, a + 50, 50 * sizeof(float));

    for (size_t i = 0; i < 50; ++i)
    {
        printf("%.3f ", b[i]);
    }
    printf("\n");
}