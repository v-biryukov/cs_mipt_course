#include <stdio.h>

void print_address(int* p)
{
    printf("%p\n", p);
}


int main()
{
    int a = 10;


    print_address(&a);  // Можно так

    int* p = &a;
    print_address(p);   // Или так
}