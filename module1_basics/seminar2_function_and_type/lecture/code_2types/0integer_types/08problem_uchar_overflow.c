#include <stdio.h>

int main()
{
    unsigned char a = 255;
    a += 1;
    printf("%hhu\n", a);



    unsigned char b = 200;
    b += 100;
    printf("%hhu\n", b);



    unsigned char c = 10;
    c *= -1;
    printf("%hhu\n", c);



    unsigned char d = -1;
    printf("%hhu\n", d);



    unsigned char e = 2;
    e *= 130;
    printf("%hhu\n", e);
}

/*
    Задача:

        Что напечатает данная программа?
        Попытайтесь догадаться без запуска программы.

        Скомпилируйте программу и запустите и проверьте свои догадки.
*/
