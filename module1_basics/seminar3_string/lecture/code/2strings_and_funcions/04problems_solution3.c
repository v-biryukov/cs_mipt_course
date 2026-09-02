#include <stdio.h>


size_t length(const char str[]) 
{
    size_t i = 0;
    while (str[i] != '\0')
        i++;

    return i;
}


void multiply3(char str[]) 
{
    int len = (int)length(str);
    for (int i = 0; i < len; ++i) 
    {
        str[i] -= '0';
    }

    int carry = 0;
    for (int i = len - 1; i >= 0; --i)  
    {
        str[i] = 3 * str[i] + carry;
        carry = str[i] / 10;
        str[i] = str[i] % 10;
    }

    if (carry != 0) 
    {
        for (int i = len; i >= 0; --i) 
        {
            str[i + 1] = str[i];
        }
        str[0] = carry;
        len += 1;
    }

    for (int i = 0; i < len; ++i) 
    {
        str[i] += '0';
    }
}


int main() 
{
    char str[10001];
    scanf("%10000s", str);

    multiply3(str);
    printf("%s\n", str);
}