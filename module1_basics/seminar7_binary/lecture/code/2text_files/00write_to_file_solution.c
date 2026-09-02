#include <stdio.h>

int main()
{
    FILE* file = fopen("result.txt", "w");

    for (int i = 0; i <= 1000; ++i)
        fprintf(file, "%i ", i);

    fclose(file);
}
