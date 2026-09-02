#include <stdio.h>


int main() 
{
    int n;
    char str[100];

    scanf("%i%s", &n, str);

    for (int i = 0; i < n; ++i)
        printf("%s ", str);
    printf("\n");
}