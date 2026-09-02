#include <stdio.h>


int main()
{
    int a = 10;

    int* p = &a;

    int** q = &p;

    // |||||||| Пишите код ниже ||||||||

    int*** r = &q;
    ***r = 2 * ***r;

    // |||||||||||||||||||||||||||||||||

    printf("%i\n", a);

}