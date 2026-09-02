/*
    Функция strcpy
    
    char* strcpy (char a[], const char b[]))  -  Копирует строку b в строку a. Аналог a = b.


    char a[20] = "Mouse";
    char b[20] = "Elephant";

    Строки это массивы, поэтому их нельзя просто присваивать:
    
        a = b;  // Не работает

    Это не будет работать! Нужно использовать strcpy:

        strcpy(a, b);
*/



#include <stdio.h>
#include <string.h>

int main() 
{
    char a[20] = "Mouse";
    char b[20] = "Elephant";

    printf("a = %s, b = %s\n", a, b);

    strcpy(a, b);

    printf("a = %s, b = %s\n", a, b);
}


/*
    Задача:

        Напишите функцию  void swap(char a[], char b[]) которая будет менять значения строк a и b.
        Известно, что каждая строка меньше 50-ти символов.
        Используйте функцию strcpy.
        

        Этот код:

            char a[20] = "Mouse";
            char b[20] = "Elephant";

            printf("a = %s, b = %s\n", a, b);

            swap(a, b);

            printf("a = %s, b = %s\n", a, b);

        Должен напечатать:

            a = Mouse, b = Elephant
            a = Elephant, b = Mouse
*/