
#include <stdio.h>

int main()
{
    char a[10] = "Cat";
    printf("%s\n", a);

    a[2] = 'm';
    a[3] = 'e';
    a[4] = 'l';
    a[5] = '\0';

    printf("%s\n", a);
}