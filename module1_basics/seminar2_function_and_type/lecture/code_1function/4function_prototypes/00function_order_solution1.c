/*
    Ошибка возникала из-за того что в программе была сначала написана функция print_primes, а потом is_prime.
    Но в функции print_primes была использована функция is_prime, которая была написана позже.
    Можно сказать, что функция print_primes не знает о функции is_prime, так как is_prime была написана позже.

    Чтобы решить эту проблему достаточно просто поменять местами определение двух функций, 
    как это сделана в этой программе.
*/


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
    print_primes(100, 150);
}