#include <stdio.h>

int main()
{
    char a[10] = {67, 97, 116, 49, 50, 51, 0};
    char b[10] = {'C', 'a', 't', '1', '2', '3', '\0'};
    char c[10] = "Cat123";

    printf("%s\n", a);
    printf("%s\n", b);
    printf("%s\n", c);
    
}