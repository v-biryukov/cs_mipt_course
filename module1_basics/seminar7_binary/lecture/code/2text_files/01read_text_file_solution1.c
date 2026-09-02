#include <stdio.h>

int main()
{
    FILE* file = fopen("numbers.txt", "r"); 

    int n;
    fscanf(file, "%i", &n);

    int sum = 0;

    for (int i = 0; i < n; ++i)
    {
        int a;
        fscanf(file, "%i", &a);
        sum += a;
    }

    printf("Sum = %i\n", sum);

    fclose(file);
}