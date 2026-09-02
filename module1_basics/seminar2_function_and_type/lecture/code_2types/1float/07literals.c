/*
    Числовые литералы

    Числовой литерал - это просто число непосредственно в теле программы.
    Например, когда мы пишем:

        int a = 10;    или    printf("%i\n", 10);    
    
    то в этом случае 10 является числовым литералом.

    Также как и у переменные, у литералов есть тип. Например, тип литерала 10 (или любого целого числа) это int.
    Изменить тип литерала можно добавив специальный суффикс после числа:

        10      это int
        10u     это unsigned int
        10ll    это long long
        10ull   это unsigned long long


    Тип литерала числа с точкой - это double. Например, тип литерала 2.5 (или любого числа с точкой) это double.

        2.5     это double
        2.5f    это float
*/


#include <stdio.h>

int main()
{
    printf("Integer literals:\n");
    printf("%i\n", sizeof(10));
    printf("%i\n", sizeof(10u));
    printf("%i\n", sizeof(10ll));
    printf("%i\n", sizeof(10ull));

    printf("Floating literals:\n");
    printf("%i\n", sizeof(2.5));
    printf("%i\n", sizeof(2.5f));
}