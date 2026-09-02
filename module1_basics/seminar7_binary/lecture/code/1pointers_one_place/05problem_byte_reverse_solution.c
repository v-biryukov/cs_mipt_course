#include <stdio.h>

int main()
{
    unsigned int a;
    scanf("%x", &a);


    // |||||||  Ваш код ниже  ||||||||||||



    for (int i = 0; i < sizeof(a) / 2; ++i)
    {
        char* p = (char*)&a + i;
        char* q = (char*)&a + sizeof(a) - 1 - i;
        

        char temp = *p;
        *p = *q;
        *q = temp;
    }


    // |||||||||||||||||||||||||||||||||||

    printf("%x\n", a);
}