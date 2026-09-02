#include <stdio.h>

int main() 
{
    for (int a = 2; a <= 5000; ++a)
    {
        int is_prime = 1;

        for (int i = 2; i * i <= a; ++i)
        {
            if (a % i == 0)
            {
                is_prime = 0;
                break;
            }
        }

        if (is_prime)
            printf("%i ", a);
    }
    printf("\n");
}