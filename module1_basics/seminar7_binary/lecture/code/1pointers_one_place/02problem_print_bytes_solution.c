#include <stdio.h>


int main()
{
    unsigned int a = 0xaa99bb88;

    unsigned char* p = &a;

    for (int i = 0; i < sizeof(a); ++i)
    {
        printf("%02x ", p[i]);
    }
    printf("\n");
}