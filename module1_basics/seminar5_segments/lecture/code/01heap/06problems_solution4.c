#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book 
{
    char title[50];
    int pages;
    float price;
};
typedef struct book Book;

void print_book(const Book* pb) 
{
    printf("Book: %s, Pages: %i, Price: %g\n", pb->title, pb->pages, pb->price);
}

int main()
{
    Book* p = (Book*)malloc(sizeof(Book));
    
    strcpy(p->title, "War and Peace");
    p->pages = 1225;
    p->price = 2000.0;

    print_book(p);

    free(p);
}