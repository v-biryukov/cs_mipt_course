#include <stdio.h>


void brackets(int n)
{
    if (n <= 0)
        return;

    printf("(");
    brackets(n - 1);
    printf(")");
}

int main()
{
    brackets(4);
    printf("\n");

    brackets(10);
    printf("\n");
}

