#include <stdio.h>


int main()
{
    unsigned char a[256];

    for (int i = 0x00; i <= 0xff; ++i)
    {
        a[i] = i;
    }



    for (size_t i = 0; i < 256; ++i)
    {
        printf("%02hhx ", a[i]);
    }
    printf("\n");
}
