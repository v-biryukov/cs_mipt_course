#include <stdio.h>


void sort(char str[]) 
{
    for (int i = 0; str[i] != '\0'; ++i) 
    {
        int min_index = i;
        for (int j = i; str[j]; ++j)
        {
            if (str[j] < str[min_index])
                min_index = j;
        }

        char temp = str[i];
        str[i] = str[min_index];
        str[min_index] = temp;
    }
}


int main() 
{
    char str[201];
    scanf("%200[^\n]", str);

    sort(str);
    
    printf("%s\n", str);
}