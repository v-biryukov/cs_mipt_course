/*
    Прототип функции

    Очень часто, особенно в больших программах, можно увидеть как сначала пишутся прототипы всех
    функций (за исключением функции main), а потом эти функции описываются в коде программы.
    В этом случае о порядке написания функций можно вообще никак не заботиться.
*/


#include <stdio.h>


int is_prime(int number);
void print_primes(int a, int b);



int main() 
{
    print_primes(100, 150);
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