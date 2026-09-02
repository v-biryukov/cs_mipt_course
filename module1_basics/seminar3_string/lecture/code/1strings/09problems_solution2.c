#include <stdio.h>

int main() 
{
    char str[100];
    scanf("%s", str);
    
    for (int i = 0; str[i] != '\0'; ++i)
    {
        printf("%c%c", str[i], str[i]);
    }

    printf("\n");
}