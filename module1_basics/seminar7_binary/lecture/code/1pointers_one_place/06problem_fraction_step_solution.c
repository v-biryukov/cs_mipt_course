#include <stdio.h>


int main()
{
    unsigned int a[3] = {0x11223344, 0xaabbccdd, 0x99887766};
        
    unsigned int* p = &a[0];

    // |||||||  Ваш код ниже  ||||||||||||


    p = (unsigned int*) ((char*)p + 3);

    // |||||||||||||||||||||||||||||||||||

    printf("%x\n", *p); // Должно напечатать bbccdd11
}