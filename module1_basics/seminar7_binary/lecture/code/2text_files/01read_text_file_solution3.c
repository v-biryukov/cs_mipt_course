#include <stdio.h>

int main()
{
    FILE* file = fopen("numbers_no_count.txt", "r"); 

    int sum = 0;

    while (1)
    {
        int a;
        int x = fscanf(file, "%i", &a);

        if (x == EOF)
            break;

        sum += a;
    }

    printf("Sum = %i\n", sum);

    fclose(file);
}