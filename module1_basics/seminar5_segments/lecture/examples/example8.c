#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data
{
    int* numbers;
    char* symbols;
};
typedef struct data Data;


int main()
{
    Data* p = (Data*)malloc(sizeof(Data));
    p->numbers = (int*)malloc(sizeof(int) * 3);
    p->symbols = (char*)malloc(sizeof(char) * 14);

    p->numbers[0] = 100;
    p->numbers[1] = 200;
    p->numbers[2] = 300;

    strcpy(p->symbols, "Cats and Dogs");

    
    for (size_t i = 0; i < 3; ++i)
        printf("%i ", p->numbers[i]);
    printf("\n");

    printf("%s\n", p->symbols);

    free(p->numbers);
    free(p->symbols);
    free(p);
}