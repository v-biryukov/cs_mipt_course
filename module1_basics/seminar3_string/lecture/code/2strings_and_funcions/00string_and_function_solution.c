#include <stdio.h>

void change_letter(char str[], char from, char to)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == from)
            str[i] = to;
    }
}


int main()
{
    char str[100] = "Cats and dogs";

    change_letter(str, 'a', 'o');
    change_letter(str, 's', 'i');

    printf("%s\n", str);
}