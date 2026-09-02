#include <stdio.h>


int main()
{
    char array[20];

    for (int i = 0; i < 20; ++i)
        printf("%p\n", &array[i]);

    for (int i = 0; i < 20; ++i)
        printf("%llu\n", &array[i]);
}