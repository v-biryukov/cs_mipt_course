#include <stdio.h>

int main()
{
    int i = 1;

    while (i < 1000)
    {
        if (i % 7 == 0)
            printf("%i ", i);

        i += 1;
    }
    printf("\n");
}


