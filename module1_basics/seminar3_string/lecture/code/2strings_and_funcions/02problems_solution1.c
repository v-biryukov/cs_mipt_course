#include <stdio.h>

size_t length(const char str[])
{
    int i = 0;

    while (str[i] != '\0')
        ++i;

    return i;
}


int main()
{
    char str[201];
    scanf("%200s", str);

    printf("%zu\n", length(str));
}