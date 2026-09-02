#include <stdio.h>
#include <string.h>

int main() 
{
    char a[100];
    char b[100];
    char c[100];

    scanf("%s%s%s", a, b, c);


    char temp[100];
    if (strcmp(a, b) > 0)
        strcpy(temp, a);
    else
        strcpy(temp, b);


    if (strcmp(temp, c) > 0)
        printf("%s\n", temp);
    else
        printf("%s\n", c);
}