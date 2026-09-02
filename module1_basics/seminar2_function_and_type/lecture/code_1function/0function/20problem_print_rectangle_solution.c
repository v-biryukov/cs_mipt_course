#include <stdio.h>



void print_rectangle(int a, int b) 
{
    for (int i = 0; i < a; ++i) 
    {
        for (int j = 0; j < b; ++j)
            printf("*");

        printf("\n");
    }
}

int main()
{
    print_rectangle(4, 10);
    print_rectangle(8, 2);
}