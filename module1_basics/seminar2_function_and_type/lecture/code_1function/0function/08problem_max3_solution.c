#include <stdio.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int main()
{
    int a, b, c;
    scanf("%i%i%i", &a, &b, &c);
    
    printf("%i\n", max(max(a, b), c));
}