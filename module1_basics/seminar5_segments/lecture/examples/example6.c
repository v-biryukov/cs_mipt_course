#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 123;

    int** p = (int**)malloc(sizeof(int*));
    
    *p = &a;

    printf("%i\n", **p);

    free(p);
}