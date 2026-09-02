/*
    Задача:

        Эта программа считывает 2 числа и печатает все простые числа, находящиеся между считанными числами.

        Напишите функцию print_primes которая будет принимать 2 числа a и b.
        Эта функция должна печатать все простые числа на отрезке [a, b].

        Используйте функцию is_prime внутри функции print_primes, чтобы проверить числа на простоту.

        !!  Чтобы функцию is_prime можно было использовать в функции print_primes,
            нужно чтобы функция is_prime была написана до функции print_primes.
            Иначе в функции print_primes мы не будем знать, что функция is_prime существует.
*/



#include <stdio.h>

int is_prime(int number)
{
    if (number < 2)
        return 0;

    int result = 1;
    for (int i = 2; i * i <= number; ++i)
    {
        if (number % i == 0)
        {
            result = 0;
            break;
        }
    }
    
    return result;
}


int main() 
{
    int a, b;
    scanf("%i%i", &a, &b);

    for (int number = a; number <= b; ++number)
    {
        if (is_prime(number))
            printf("%i ", number);
    }
    printf("\n");
}