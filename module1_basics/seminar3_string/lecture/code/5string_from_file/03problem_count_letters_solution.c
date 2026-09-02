#include <stdio.h>
#include <string.h>
#include <ctype.h>
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


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Error! This program need input file.\n");
        printf("To call this program use:\n");
        printf("%s <input_file_name>\n", argv[0]);
        return 1;
    }

    char str[BUFFER_SIZE];
    read_file_to_string(argv[1], str);

    int counts[26] = {0};
    for (int i = 0; str[i]; ++i)
    {
        if (islower(str[i]))
            counts[str[i] - 'a']++;

        if (isupper(str[i]))
            counts[str[i] - 'A']++;
        
    }

    for (int i = 0; i < 26; ++i)
        printf("%c: %i\n", 'a' + i, counts[i]);
}