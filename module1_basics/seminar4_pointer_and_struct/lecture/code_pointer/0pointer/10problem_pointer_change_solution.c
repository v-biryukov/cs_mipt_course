#include <stdio.h>


int main()
{
    int a = 0;
    int b = 0;
    int c = 0;

    int* p = &a;

    // Пишите ваш код ниже


    *p = 10;

    p = &b;
    *p = 20;

    p = &c;
    *p = 30;


    // ||||||||||||||||||||

    printf("%i %i %i\n", a, b, c);
}


