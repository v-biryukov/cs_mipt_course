#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1000000

void read_file_to_string(const char filename[], char str[])
{
    FILE* f = fopen(filename, "r");
    
    int i = 0;
    while (1)
    {
        int c = fgetc(f);
        if (c == EOF)
            break;

        str[i] = (char)c;
        i += 1;
    }
    str[i] = '\0';

    fclose(f);
}

void save_string_to_file(const char filename[], const char str[])
{
    FILE* f = fopen(filename, "w");
    fprintf(f, "%s", str);
    fclose(f);
}


int main()
{
    char str[BUFFER_SIZE];
    read_file_to_string("three_little_pigs.txt", str);

    int size = strlen(str);
    for (int i = 0; i < size; ++i)
    {
        if (str[i] == 'i')
            str[i] = 'u';
    }

    save_string_to_file("result.txt", str);
}