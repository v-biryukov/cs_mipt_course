#include <stdio.h>


int to_int(const char str[])
{
    int result;
    sscanf(str, "%i", &result);
    return result;
}


int main() 
{
    char a[10] = "1234";
    char b[10] = "456";

    printf("%i\n", to_int(a) + to_int(b));
}