/*
    Представлено 2 решения
*/


#include <stdio.h>
#include <ctype.h>


void capitalize(char* s)
{
    for (size_t i = 0; s[i]; ++i)
        s[i] = toupper(s[i]);
}


void capitalize2(char* s)
{
    for (; *s; ++s)
        *s = toupper(*s);
}


int main()
{
    char a[50] = "Tiger123";
    
    printf("%s\n", a);

    capitalize2(a);

    printf("%s\n", a);
}