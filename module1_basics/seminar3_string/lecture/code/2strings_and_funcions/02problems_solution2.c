#include <stdio.h>

size_t length(const char str[])
{
    int i = 0;
    while (str[i] != '\0')
        ++i;

    return i;
}

void reverse(char str[]) 
{
    int n = length(str);

    for (int i = 0; i < n / 2; ++i) 
    {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}


int main() 
{
    char str[200];
    scanf("%s", str);

    reverse(str);
    printf("%s\n", str);
}
