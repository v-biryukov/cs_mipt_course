#include <stdio.h>


void print_even(int a, int b) 
{
    if (a % 2 == 1)
        a += 1;

    for (int i = a; i <= b; i += 2)
        printf("%i ", i);
    
    printf("\n");
}

void print_n_times(int a, int n) 
{
    for (int i = 0; i < n; ++i)
        printf("%i ", a);

    printf("\n");
}

void print_rectangle(int a, int b) 
{
    for (int i = 0; i < a; ++i) 
    {
        for (int j = 0; j < b; ++j)
            printf("*");

        printf("\n");
    }
}


void multi(int type, int a, int b) 
{
    if (type == 1)
        print_even(a, b);
    else if (type == 2)
        print_n_times(a, b);
    else if (type == 3)
        print_rectangle(a, b);
    else
        printf("Error!\n");
}



int main()
{
    multi(1, 2, 8);
    multi(2, 2, 8);
    multi(3, 2, 8);
    multi(10, 2, 8);
}