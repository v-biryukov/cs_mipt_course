#include <stdio.h>

int main() 
{
    char str[100];
    scanf("%s", str);

    int i = 0;
    while (str[i] != '\0' && str[i] != '.') 
        i++;

    str[i] = '\0';

    printf("%s\n", str);
}