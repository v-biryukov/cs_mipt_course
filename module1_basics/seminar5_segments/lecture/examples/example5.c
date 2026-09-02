#include <stdio.h>
#include <stdlib.h>

int main()
{
    int** p = (int**)malloc(sizeof(int*));
    
    *p = (int*)malloc(sizeof(int));

    **p = 123;

    printf("%i\n", **p);

    free(*p);
    free(p);
}