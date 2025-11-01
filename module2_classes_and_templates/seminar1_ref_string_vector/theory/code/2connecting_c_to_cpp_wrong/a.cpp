/*
    Неправильное подключение файла C файла к C++ файлу.
    Будет ошибка из-за манглирования если скомпилировать C файл компилятором gcc, 
    а C++ файл компилятором g++, а потом слинковать.

        g++ -c a.cpp
        gcc -c b.c

        g++ a.o b.o

    Возникает ошибка из-за того, что в файле b.o функция bison называется как bison,
    а в файле a.o функция bison называется примерно как _Z5bisoni.

    Используйте команды strings, xxd или hexdump -C, чтобы посмотреть как называются символы
    в файлах a.o и b.o.
*/


#include <iostream>
#include <string>
#include "b.h"

void axolotl(int x)
{
    std::cout << "axolotl's int x = " << x << std::endl;
}


int main()
{
    axolotl(100);
    bison(200);
}