#include <stdio.h>
#include <math.h>


float distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


int main()
{
    printf("%f\n", distance(0, 0, 1, 1));
    printf("%f\n", distance(-1, 1, 0, 0));
    printf("%f\n", distance(0, 0, 5000, 0));

    printf("%f\n", distance(7, -3, -5, 4));
}