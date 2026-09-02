#include <stdio.h>

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

int is_expensive(const Book* pb)
{
    return pb->price > 1000.0f;
}

float get_price_by_page(const Book* pb)
{
    return pb->price / pb->pages;
}

int main() 
{
    Book a = {"The Martian", 300, 600};

    printf("Is expensive? %i\n", is_expensive(&a));
    printf("Price of one page? %f\n", get_price_by_page(&a));
}