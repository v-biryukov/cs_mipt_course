#include <stdio.h>

int main()
{
    FILE* file = fopen("data.bin", "rb");

    fseek(file, 7, SEEK_SET);

    unsigned int a;
    fread(&a, sizeof(int), 1, file);

    printf("%x\n", a);

    fclose(file);
}