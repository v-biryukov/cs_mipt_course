/*
    Прототип функции

    В прототипах функций необязательно указывать имена параметров. Достаточно просто указать их типы.
    То есть вместо того чтобы писать:

        int is_prime(int number);

    Можно написать так:

        int is_prime(int);

    И это логично, ведь на тот момент когда компилятор читает прототип, ему нужно знать лишь имя функции,
    типы параметоров функции и тип возвращаемого значения.
    Этой информации для компилятора достаточно, чтобы понять, что функция вызывается правильно.
*/


#include <stdio.h>


int is_prime(int);
void print_primes(int, int);



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