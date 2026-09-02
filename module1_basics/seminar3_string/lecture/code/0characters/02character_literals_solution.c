#include <stdio.h>

int main() 
{
    char x;
    scanf("%c", &x);
    
    if (x >= 'a' && x <= 'z')
        x -= ('a' - 'A');

    printf("%c\n", x);
}