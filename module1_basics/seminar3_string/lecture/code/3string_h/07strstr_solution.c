#include <stdio.h>
#include <string.h>

void chage_cat_to_dog(char str[])
{
    char* p = strstr(str, "cat");

    if (p == NULL)
        return;

    p[0] = 'd';
    p[1] = 'o';
    p[2] = 'g';
}


int main() 
{
    char a[100] = "hello cat!";

    printf("%s\n", a);
    chage_cat_to_dog(a);
    printf("%s\n", a);
}