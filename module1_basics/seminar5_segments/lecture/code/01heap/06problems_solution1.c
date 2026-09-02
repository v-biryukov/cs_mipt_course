#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* p = (char*)malloc(sizeof(char));
    *p = 'A';

    printf("%c\n", *p);

    free(p);
}