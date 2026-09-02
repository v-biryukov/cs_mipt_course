/*
    Использование typedef для сокращения названия структуры.

    Вы могли заметить, что название типа структуры начинается со слова struct.
    Таким образом название типа структуры состоит из двух слов, например struct point или struct book.
    Писать постоянно название типа, состоящее из двух слов может быть утомительно.
    Но мы можем использовать typedef чтобы сократить названия типа структур.

    Допустим, нам надоело писать везде struct book и мы хотим вместо этого писать везде просто Book.
    Для этого просто создадим новое имя типа Book, которое будет равно struct book:

        typedef struct book Book;

    Всё, теперь вместо struct book мы можем везде писать Book.
*/

#include <stdio.h>
#include <string.h>

struct book 
{
    char title[50];
    int pages;
    float price;
};
typedef struct book Book;

void print_book(Book b) 
{
    printf("Book: %s, Pages: %i, Price: %g\n", b.title, b.pages, b.price);
}

void print_books(Book* books, size_t n) 
{
    for (size_t i = 0; i < n; ++i)
        print_book(books[i]);
}

int main() 
{
    Book a = {"The Martian", 100, 550.0};
    print_book(a);

    a.pages = 369;
    strcpy(a.title, "The Catcher in the Rye");
    print_book(a);

    Book scifi_books[10] = {{"Dune", 300, 500.0}, {"Fahrenheit 451", 400, 700.0}, {"Day of the Triffids", 304, 450.0}};
    scifi_books[2].price = 2000.0;
    print_books(scifi_books, 3);
}