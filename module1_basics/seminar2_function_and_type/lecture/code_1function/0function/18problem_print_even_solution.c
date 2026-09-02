#include <stdio.h>

void print_even(int a, int b) 
{
    if (a % 2 == 1)
        a += 1;

    for (int i = a; i <= b; i += 2)
        printf("%i ", i);
    
    printf("\n");
}



int main()
{
    print_even(1, 20);
    print_even(1000, 1100);
}