#include <stdio.h>
#include <string.h>

#define NUM_STRINGS 15
#define BUFFER_SIZE 20


void print_strings(const char strings[][BUFFER_SIZE], int num_strings)
{
    for (int i = 0; i < num_strings; ++i)
        printf("%s ", strings[i]);
    printf("\n");
}

void sort_strings(char strings[][BUFFER_SIZE], int num_strings)
{
    for (int i = 0; i < num_strings; ++i) 
    {
        int min_index = i;
        for (int j = i + 1; j < num_strings; ++j)
            if (strcmp(strings[j], strings[min_index]) < 0)
                min_index = j;


        char temp[BUFFER_SIZE];
        strcpy(temp, strings[i]);
        strcpy(strings[i], strings[min_index]);
        strcpy(strings[min_index], temp);
    }

}

int main() 
{
    char animals[NUM_STRINGS][BUFFER_SIZE] = 
    {
        "Cat", "Dog", "Mouse", "Tiger", "Elephant", "Axolotl", "Monkey",
        "Kangaroo", "Walrus", "Bat", "Orca", "Wolf", "Panda", "Bee", "Hippo"
    };

    print_strings(animals, NUM_STRINGS);
    sort_strings(animals, NUM_STRINGS);
    print_strings(animals, NUM_STRINGS);
}