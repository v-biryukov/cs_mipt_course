#include <stdio.h>


int main()
{
    char str[201];
    scanf("%200[^\n]", str);

    
    for (int i = 0; str[i]; ++i)
    {
        if (str[i] == ' ')
            str[i] = '\n';
    }

    printf("%s\n", str);
}