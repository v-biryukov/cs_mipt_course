/*
    Не самое эффективное решение
*/


#include <stdio.h>

int main()
{
    for (int i = 1; i <= 1000; ++i)
    {
        if (i % 17 == 0)
            printf("%i ", i);
    }
    printf("\n");
}


