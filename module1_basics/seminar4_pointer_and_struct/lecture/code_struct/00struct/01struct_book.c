/*
    Структуры

        Чтобы создать тип данных, описывающий книгу в книжном магазине, нужно написать так:

            struct book
            {
                char title[50];
                int pages;
                float price;
            };

        После того, как мы это написали, у нас появился новый тип данных, по имени struct book.
        Чтобы создать переменную типа struct book по имени a нужно написать:

            struct book a;
        
        Переменная a типа struct book хранит в себе 3 объекта типов char[50], int и float под именами title, pages и price.
        Получить доступ к внутренностям переменной a можно с помощью оператора . (точка). Вот так:
            
            strcpy(a.title, "War and Peace");
            a.pages = 1200;
            a.price = 900;

        Помните, что в языке C нельзя присваивать строку просто так, для этого нужно использовать функцию strcpy
        из библиотеки string.h.
*/


#include <stdio.h>
#include <string.h>

struct book
{
    char title[50];
    int pages;
    float price;
};

int main()
{
    struct book a;
    
    strcpy(a.title, "War and Peace");
    a.pages = 1200;
    a.price = 900;
    
    printf("%s, pages = %i, price = %.2f\n", a.title, a.pages, a.price);
}