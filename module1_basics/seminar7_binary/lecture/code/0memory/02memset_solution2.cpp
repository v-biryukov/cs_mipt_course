#include <stdio.h>
#include <string.h>


int main()
{
    char a[1001];

    memset(a, 'a', 1000);
    a[1000] = '\0';


    printf("%s\n", a);
}