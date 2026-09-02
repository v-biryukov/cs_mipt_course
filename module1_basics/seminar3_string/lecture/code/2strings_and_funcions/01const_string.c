/*
    Передача строк в функции

    Если вы пишет функцию, которая не должна менять строку, то нужно обязательно принимать эту строку 
    как константную:
    
        const char str[]

    Например, в данном примере, функция is_empty возвращает 1, если строка пуста и 0 иначе.
    Эта функция не меняет строку, поэтому очень важно написать, что она принимает константную строку.
*/



#include <stdio.h>

int is_empty(const char str[])
{
    return str[0] == '\0';
}


int main()
{
    char a[100] = "Cats and dogs";
    char b[100] = "";


    printf("Is string a empty? %i\n", is_empty(a));
    printf("Is string b empty? %i\n", is_empty(b));
}