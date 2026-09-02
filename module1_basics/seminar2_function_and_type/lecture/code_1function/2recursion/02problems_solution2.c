#include <stdio.h>


void counter(int n)
{
    if (n == 0)
        return;
    
    printf("%i ", n);
    counter(n / 2);
}

int main()
{
    counter(100);
}
