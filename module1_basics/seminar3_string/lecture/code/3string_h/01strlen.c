/*
    Функция strlen

    Функция strlen вычисляет длину строки, то есть количество символов от начала строки 
    и до нулевого символа.

        size_t strlen(const char str[])

    Чтобы это сделать, функция проходит всю строку от начала и пока не встретит нулевой символ.
    Поэтому эта функцию работает достаточно долго для такой базовой операции.
    Если это не учитывать, то можно сделать ошибки, подобные той, что есть в этой программе.
*/



#include <stdio.h>
#include <string.h>

int main() 
{
    char str[1000] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore "
                     "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
                     "aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum "
                     "dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui "
                     "officia deserunt mollit anim id est laborum";

    printf("%s\n", str);


    for (size_t i = 0; i < strlen(str); ++i)
    {
        if (str[i] == ' ')
            str[i] = '\n';
    }

    printf("%s\n", str);
}


/*
    Задача:

        В этой программы мы меняем все пробелы в строке на символы переноса строки.
        И вроде бы всё работает, но в этой программе есть серьёзная ошибка.
        Из-за которой программа работает намного медленней, чем могла бы.

        Найдите эту ошибку и исправьте.
*/