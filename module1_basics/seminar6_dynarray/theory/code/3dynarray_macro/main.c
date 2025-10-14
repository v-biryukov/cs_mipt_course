#include <stdio.h>
#include <string.h>
#include "dynarray.h"

struct book
{
    char title[30];
    int pages;
    float price;
};
typedef struct book Book;

void print_book(Book pb)
{
    printf("%s, pages = %i, price = %f\n", pb.title, pb.pages, pb.price);
}

DECLARE_DYNARRAY(int)
DECLARE_DYNARRAY(float)
DECLARE_DYNARRAY(Book)
DECLARE_DYNARRAY(Dynarray_int)


int main() 
{

    // ||||||||||||||||||||| dynarray of ints  |||||||||||||||||||||

    Dynarray_int a;
    dynarray_int_init(&a, 0);
    for (size_t i = 0; i < 100; ++i)
    {
        dynarray_int_push_back(&a, i);
    }
    
    for (size_t i = 0; i < a.size; ++i)
    {
        printf("%i ", dynarray_int_get(&a, i));
    }
    printf("\n");
    dynarray_int_destroy(&a);
   

    // ||||||||||||||||||||| dynarray of floats  |||||||||||||||||||||

    Dynarray_float b;
    dynarray_float_init(&b, 0);
    for (size_t i = 0; i < 100; ++i)
    {
        dynarray_float_push_back(&b, i * 3.14159265);
    }
    
    for (size_t i = 0; i < b.size; ++i)
    {
        printf("%f ", dynarray_float_get(&b, i));
    }
    printf("\n");
    dynarray_float_destroy(&b);


    // ||||||||||||||||||||| dynarray of structs  |||||||||||||||||||||

    Dynarray_Book c;
    dynarray_Book_init(&c, 0);
    
    Book temp = {"Don Quixote", 100, 199.9};
    dynarray_Book_push_back(&c, temp);
    strcpy(temp.title, "Pride and Prejudice");
    temp.pages = 200;
    temp.price = 299.9;
    dynarray_Book_push_back(&c, temp);
    strcpy(temp.title, "The Catcher in the Rye");
    temp.pages = 300;
    temp.price = 399.9;
    dynarray_Book_push_back(&c, temp);

    
    for (size_t i = 0; i < c.size; ++i)
    {
        print_book(dynarray_Book_get(&c, i));
    }
    printf("\n");
    dynarray_Book_destroy(&c);



    // ||||||||||||||||||||| dynarray of dynarrays of ints  |||||||||||||||||||||

    Dynarray_Dynarray_int d;
    dynarray_Dynarray_int_init(&d, 0);
    for (size_t i = 0; i < 10; ++i)
    {
        Dynarray_int temp;
        dynarray_int_init(&temp, 0);
        for (size_t j = 0; j < 10; ++j)
            dynarray_int_push_back(&temp, 10 * i + j);
        dynarray_Dynarray_int_push_back(&d, temp);
    }
    
    for (size_t i = 0; i < d.size; ++i)
    {
        Dynarray_int temp = dynarray_Dynarray_int_get(&d, i);
        for (size_t j = 0; j < i + 1; ++j)
            printf("%i ", dynarray_int_get(&temp, j));
        printf("\n");
    }
    printf("\n");

    for (size_t i = 0; i < d.size; ++i)
    {
        Dynarray_int temp = dynarray_Dynarray_int_get(&d, i);
        dynarray_int_destroy(&temp);
    }
    dynarray_Dynarray_int_destroy(&d);
}
