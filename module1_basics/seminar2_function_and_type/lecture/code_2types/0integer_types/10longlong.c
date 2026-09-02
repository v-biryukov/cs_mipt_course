/*
    Целые числа типа long long и unsigned long long.

    Числа типа long long и unsigned long long обычно имеет размер в 8 байта, что равно 64 бит.
    Следовательно, такие числа могут принимать 2^64 = 18446744073709551616 различных значений.


    Диапазон допустимых значений для long long:

        от -9223372036854775808 до 9223372036854775807

    Диапазон допустимых значений для unsigned long long:

        от 0 до 18446744073709551615


    !!  Обратите внимание, что для печати и считывания таких чисел в функциях printf и scanf
        используются спецификаторы:

            %lli   для типа long long
            %llu   для типа unsigned long long


    Также как и для типов int и unsigned int, переполнение числа типа unsigned long long допустимо,
    а переполнение числа типа long long приводит к Undefined Behaviour.
*/

#include <stdio.h>

int main()
{
    long long a = 40000000000;
    long long b = 50000000000;
    long long c = a + b;

    printf("%lli\n", c);

    
    unsigned long long x = 123456789123456789;
    unsigned long long y = 234567891234567891;
    unsigned long long z = x + y;

    printf("%llu\n", z);
}