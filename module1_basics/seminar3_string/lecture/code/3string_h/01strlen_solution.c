/*
    Ошибка заключается в том в этом участке кода:

        for (size_t i = 0; i < strlen(str); ++i)
        {
            if (str[i] == ' ')
                str[i] = '\n';
        }

    Функция strlen вызывается в начале каждой итерации цикла и вычисляет длину строки str.
    Чтобы вычислить длину строки, strlen проходит всё строку от начала до нулевого символа.
    Получается, что данный цикл работает за O(n^2) что очень медленно.


    Правильно написать так:
    
        size_t n = strlen(str);
        for (size_t i = 0; i < n; ++i)
        {
            if (str[i] == ' ')
                str[i] = '\n';
        }

    или так:

        for (size_t i = 0; str[i]; ++i)
        {
            if (str[i] == ' ')
                str[i] = '\n';
        }
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

    size_t n = strlen(str);
    for (size_t i = 0; i < n; ++i)
    {
        if (str[i] == ' ')
            str[i] = '\n';
    }

    printf("%s\n", str);
}

