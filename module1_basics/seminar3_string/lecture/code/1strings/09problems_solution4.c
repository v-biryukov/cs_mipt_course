#include <stdio.h>

int main() 
{
    char str[1001];
    scanf("%s", str);

    int sum = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        sum += str[i] - '0';
    }

    printf("%i\n", sum);
}