/*
    Целые числа типа short и unsigned short.

    Числа типа short и unsigned short обычно имеет размер в 2 байта, что равно 16 бит.
    Следовательно, такие числа могут принимать 2^16 = 65536 различных значений.


    Диапазон допустимых значений для short:

        от -32768 до 32767

    Диапазон допустимых значений для unsigned short:

        от 0 до 65535


    !!  Обратите внимание, что для печати и считывания таких чисел в функциях printf и scanf
        используются спецификаторы:

            %hi   для типа short
            %hu   для типа unsigned short


    Также как и для типов int и unsigned int, переполнение числа типа unsigned short допустимо,
    а переполнение числа типа short приводит к Undefined Behaviour.
*/

#include <stdio.h>

int main()
{
    short a = 400;
    short b = 500;
    short c = a + b;

    printf("%hi\n", c);

    
    unsigned short x = 40000;
    unsigned short y = 50000;
    unsigned short z = x + y;

    printf("%hu\n", z);
}


/*
    Задача:

        Что напечатает данная программа?
        Скомпилируйте её и запустите и проверьте себя.
*/