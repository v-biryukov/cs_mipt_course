#include <stdio.h>
#include <stdlib.h>

void print_fib_reverse(int n) 
{
    int* fib = (int*)malloc(n * sizeof(int));
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < n; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];
    
    for (int i = n - 1; i >= 0; --i)
        printf("%i ", fib[i]);
}

int main() 
{
    print_fib_reverse(20);
}
