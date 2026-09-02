#include <stdio.h>


int main()
{
    double a = 123.456;

    unsigned char* p = &a;

    for (int i = 0; i < sizeof(a); ++i)
    {
        printf("%02x ", p[i]);
    }
    printf("\n");
}