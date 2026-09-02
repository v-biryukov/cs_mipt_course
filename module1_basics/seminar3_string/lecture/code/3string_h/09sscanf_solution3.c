#include <stdio.h>

int main() 
{
    char str[100];
    scanf("%99[^\n]", str);

    int a, b;
    sscanf(str, "%i + %i", &a, &b);

    printf("%i\n", a + b);
}