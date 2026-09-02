#include <stdio.h>
#include <string.h>

void swap(char a[], char b[])
{
    char temp[50];

    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

int main() 
{
    char a[20] = "Mouse";
    char b[20] = "Elephant";

    printf("a = %s, b = %s\n", a, b);

    swap(a, b);

    printf("a = %s, b = %s\n", a, b);
}