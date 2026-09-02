#include <stdio.h>

int main()
{
    for (int i = 1; i <= 9; ++i)
    {
        for (int j = 1; j <= 9; ++j)
        {
            printf("%2i ", i * j);
        }
        printf("\n");
    }
}


/*
    На каждой итерации:

        мы сначала печатаем i-ю строку таблицы умножения:

            for (int j = 1; j <= 9; ++j)
            {
                printf("%2i ", i * j);
            }


        а потом печатаем перенос на новую строку:

            printf("\n");
*/