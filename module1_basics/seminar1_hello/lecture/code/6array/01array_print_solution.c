#include <stdio.h>

int main()
{
    int numbers[5];

    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 40;
    numbers[3] = 30;
    numbers[4] = 80;


    for (int i = 1; i <= 4; ++i)
        printf("%i, ", numbers[i - 1]);

    printf("%i\n", numbers[4]);
}