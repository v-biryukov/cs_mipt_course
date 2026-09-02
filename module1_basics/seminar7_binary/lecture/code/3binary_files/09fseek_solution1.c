#include <stdio.h>

int main()
{
    FILE* file = fopen("data.bin", "rb");

    fseek(file, -1, SEEK_END);

    int c = fgetc(file);
    printf("%02x\n", c);

    fclose(file);
}