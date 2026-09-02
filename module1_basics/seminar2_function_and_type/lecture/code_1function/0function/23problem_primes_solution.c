#include <stdio.h>

int is_prime(int number)
{
    if (number < 2)
        return 0;

    for (int i = 2; i * i <= number; ++i)
    {
        if (number % i == 0)
            return 0;
    }
    
    return 1;
}


void print_primes(int a, int b)
{
    for (int i = a; i <= b; ++i)
    {
        if (is_prime(i))
            printf("%i ", i);
    }
    printf("\n");
}

int main() 
{
    print_primes(1, 20);

    print_primes(100, 150);

    print_primes(10000, 10100);
}