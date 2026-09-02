/*
    Библиотека string.h

    Библиотека string.h содержит множество полезных функций для работы со строками языка C.
    Вот некоторые из них:

        size_t strlen(const char str[])             -   Вычисляет длину строки

        char* strcpy (char a[], const char b[]))    -   Копирует строку b в строку a
                                                        Аналог  a = b

        char* strcat(char a[], const char b[])      -   Добавляет копию строки b в конец строки a
                                                        Аналог  a += b

        int strcmp(const char a[], const char b[])) -   Сравнивает строки a и b лексикографически
                                                        Возвращает отрицательное число, если a < b
                                                        положительное число, если a > b
                                                        ноль, если a и b равны


        
    char a[100] = "Cat";
    char b[100] = "Dog";

    Строки это массивы, поэтому их нельзя просто присваивать:
    
        a = b;  // Не работает

    Это не будет работать! Нужно использовать strcpy:

        strcpy(a, b);

    

    Строки это массивы, поэтому их нельзя просто добавить друг к другу

        a += b;  // Не работает

    Это не будет работать! Нужно использовать strcat:

        strcat(a, b);



    Строки это массивы, поэтому их нельзя просто сравнивать
    
        if (a == b)  // Не работает

    Это не будет работать! Нужно использовать strcmp:

        if (strcmp(a, b) == 0)

*/



#include <stdio.h>
#include <string.h>

int main() 
{
    char a[100] = "Cat";
    char b[100] = "Dog";
    
    strcpy(a, "Camel");
    printf("%s\n", a);


    strcat(a, b);
    printf("%s\n", a);


    printf("%i\n", strcmp(a, b));
    printf("%i\n", strcmp(b, a));
    printf("%i\n", strcmp(a, "CamelDog"));
}