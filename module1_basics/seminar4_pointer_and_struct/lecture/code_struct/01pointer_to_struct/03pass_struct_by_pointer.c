/*
    Передача структуры в функции по указателю

    Чтобы можно было изменить структуру внутри функции нужно передавать в функцию не копию структуры, а её адрес.
    То есть функция должна принимать указатель на структуру.
*/

#include <stdio.h>

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

void change(Book* pb) 
{
    pb->price += 100;
}

int main() 
{
    Book a = {"The Martian", 300, 500};

    print_book(a);
    change(&a);
    print_book(a);
}


/*
    Задачи:

        1)  Что напечатает данная программа?

        2)  Напишите функцию void inc_pages(Book* pb) которая будет принимать указатель на книгу pb и 
            увеличивать количество страниц в книге на 1.

        3)  Напишите функцию void change_pages(Book* pb, int num_additional_pages) которая будет принимать указатель 
            на книгу pb и целое число  num_additional_pages.
            Эта функция должна увеличивать количество страниц в книге на num_additional_pages.

        4)  Напишите функцию void change_first_letter(Book* pb, char new_letter), которая будет принимать указатель
            на книгу pb и символ new_letter.
            Эта функция должна изменять первый симовол в названии книги на символ new_letter.

        5)  Напишите функцию void change_title(Book* pb, const char* new_title),  которая будет принимать указатель
            на книгу pb и строку new_title.
            Эта функция должна изменять название книги на new_title. Используйте функцию strcpy.
*/