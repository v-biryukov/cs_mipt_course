#include <stdio.h>
#include <ctype.h>

void to_upper_case1(char str[]) 
{
    for (int i = 0; str[i] != '\0'; ++i) 
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 'a' - 'A';
    }
}


void to_upper_case2(char str[]) 
{
    for (int i = 0; str[i] != '\0'; ++i) 
        str[i] = toupper(str[i]);
}


int main() 
{
    char str[201];
    scanf("%200s", str);

    to_upper_case2(str);
    printf("%s\n", str);
}


/*
    Представлено 2 решения. С использованием функции библиотеки ctype.h и без.
*/