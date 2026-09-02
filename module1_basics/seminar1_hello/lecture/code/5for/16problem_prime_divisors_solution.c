#include <stdio.h>

int main() 
{
    for (int number = 2; number <= 200; ++number)
    {
        printf("%i: ", number);
        int is_prime = 1;

        for (int divisor = 2; divisor < number; ++divisor)
        {
            if (number % divisor == 0)
            {
                printf("%i ", divisor);
                is_prime = 0;
            }
        }

        if (is_prime)
            printf("prime");

        printf("\n");
    }
}