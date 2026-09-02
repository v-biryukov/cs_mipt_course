/*
    Строка может содержать специальные символы.
*/


#include <stdio.h>

int main()
{
    char str[100] = "Cats\nand\nDogs\n\n\tThe End!";

    printf("%s\n", str);
}
