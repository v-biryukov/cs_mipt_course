#include <stdio.h>


void print_array_hex(unsigned char* a, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        printf("0x%02x ", a[i]);
    }
    printf("\n");
}



int main()
{
    unsigned char a[8] = {0x11, 0x33, 0x55, 0x77, 0x99, 0xbb, 0xdd, 0xff};
    print_array_hex(a, 8);
}