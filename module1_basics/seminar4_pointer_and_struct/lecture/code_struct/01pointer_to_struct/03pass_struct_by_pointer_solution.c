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

void inc_pages(Book* pb)
{
    pb->pages++;
}

void change_pages(Book* pb, int num_additional_pages)
{
    pb->pages += num_additional_pages;
}

void change_first_letter(Book* pb, char new_letter)
{
    if (pb->title[0] != '\0')
        pb->title[0] = new_letter;
}

void change_title(Book* pb, const char* new_title)
{
    strcpy(pb->title, new_title);
}

int main() 
{
    Book a = {"The Martian", 300, 500};
    print_book(a);


    inc_pages(&a);
    print_book(a);


    change_pages(&a, 100);
    print_book(a);


    change_first_letter(&a, 'A');
    print_book(a);


    change_title(&a, "Day of the Triffids");
    print_book(a);
}