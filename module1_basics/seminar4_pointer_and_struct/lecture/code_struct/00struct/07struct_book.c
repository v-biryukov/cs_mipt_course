/*
    Структуры могут содержать в себе не только базовые типы данных, но и более сложные типы, такие как массивы
    (в том числе строки), указатели, а также другие структуры.

    В данной программе описывается структура для удобной работы с объектами Книга (struct book).
*/

#include <stdio.h>
#include <string.h>

struct book 
{
    char title[50];
    int pages;
    float price;
};

void print_book(struct book b) 
{
    printf("Book: %s, Pages: %i, Price: %g\n", b.title, b.pages, b.price);
}

void print_books(struct book* books, size_t n) 
{
    for (size_t i = 0; i < n; ++i)
        print_book(books[i]);
}

int main() 
{
    struct book a = {"The Martian", 100, 550.0};
    print_book(a);

    a.pages = 369;
    strcpy(a.title, "The Catcher in the Rye");
    print_book(a);

    struct book scifi_books[10] = {{"Dune", 300, 500.0}, {"Fahrenheit 451", 400, 700.0}, {"Day of the Triffids", 304, 450.0}};
    scifi_books[2].price = 2000.0;
    print_books(scifi_books, 3);
}