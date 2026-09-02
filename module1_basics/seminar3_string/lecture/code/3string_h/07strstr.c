/*
    Функция strstr
    
    char* strstr(const char a[], const char bp[]) -  Находит первое вхождение строки строки b в строке a
                                                     и возвращает адрес первого символа этого вхождения.

    Если в строке a нет вхождения строки b, то функция возвращает нулевой указатель NULL
*/


#include <stdio.h>
#include <string.h>

int main() 
{
    char a[100] = "The way to find a needle in a haystack is to sit down";
    char b[10] = "needle";

    char* p = strstr(a, b);

    printf("%s\n", p);
}



/*
    Задача:

        Напишите функцию change_cat_to_dog, которая бы принимала на вход строку и заменяла одну подстроку cat на dog


            До                      После
            
            cats and dogs           dogs and dogs
            hello cat!              hello dog!
            cat cat cat             dog cat cat
            cat                     dog
            mouse                   mouse
*/