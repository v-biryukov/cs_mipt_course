#include <stdio.h>


int main()
{
    char a = 10;

    char* p = &a;

    *p *= 2;

    printf("%hhi\n", a);
}