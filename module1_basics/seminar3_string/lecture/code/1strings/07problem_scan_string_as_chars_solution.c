#include <stdio.h>
#include <ctype.h>

int main() 
{
    char str[200];

    for (int i = 0; 1; ++i) 
    {
        char x;
        scanf("%c", &x);

        if (isspace(x)) 
        {
            str[i] = '\0';
            break;
        }
        
        str[i] = x;
    }


    printf("%s\n", str);
}
