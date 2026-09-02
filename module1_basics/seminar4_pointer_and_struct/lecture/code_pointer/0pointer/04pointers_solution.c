#include <stdio.h>

int main()
{
    int  a = 10;
    int* pa = &a;

    printf("Address of a: %p\n", &a);
    printf("pa:           %p\n", pa);


    double  b = 1.5;
    double* pb = &b;

    printf("Address of b: %p\n", &b);
    printf("pb:           %p\n", pb);


    char  c = 10;
    char* pc = &c;

    printf("Address of c: %p\n", &c);
    printf("pc:           %p\n", pc);


    printf("Sizes:\n");
    printf("int      %zu\n", sizeof(int));
    printf("int*     %zu\n", sizeof(int*));
    printf("double   %zu\n", sizeof(double));
    printf("double*  %zu\n", sizeof(double*));
    printf("char     %zu\n", sizeof(char));
    printf("char*    %zu\n", sizeof(char*));

}