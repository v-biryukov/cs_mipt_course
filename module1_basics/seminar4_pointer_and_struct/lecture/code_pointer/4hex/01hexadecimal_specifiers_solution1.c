#include <stdio.h>


int main()
{
    unsigned char a;

    scanf("%hhu", &a);

    printf("%hhx\n", a);


    // Чтобы всегда печатать 2 символа:
    printf("%02hhx\n", a);
}