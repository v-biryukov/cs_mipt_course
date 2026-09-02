#include <stdio.h>
#include <stdlib.h>

int main()
{
    int** p = (int**)malloc(3 * sizeof(int*));
    
    for (size_t i = 0; i < 3; ++i)
        p[i] = (int*)malloc(sizeof(int));
    
    *p[0] = 100;
    *p[1] = 200;
    *p[2] = 300;
    
    for (size_t i = 0; i < 3; ++i)
        printf("%i ", *p[i]);
    printf("\n");

    for (size_t i = 0; i < 3; ++i)
        free(p[i]);
    free(p);
}