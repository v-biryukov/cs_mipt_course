#include <stdio.h>
#include <string.h>

struct book 
{
    char title[50];
    int pages;
    float price;
};
typedef struct book Book;

void print_book(struct book b) 
{
    printf("Book: %s, Pages: %i, Price: %g\n", b.title, b.pages, b.price);
}

int main() 
{
    Book a = {"The Martian", 300, 500};
    Book* p = &a;
    print_book(a);


    (*p).pages += 1;
    print_book(a);


    (*p).title[4] = 'B';
    print_book(a);


    strcpy((*p).title, "Harry Potter and the Philosopher's Stone");
    print_book(a);
}