#include <stdio.h>


void set_time_string(const char str[], int* phours, int* pminutes)
{
    sscanf(str, "%i:%i", phours, pminutes);
}


int main() 
{
    char str[20] = "06:20";

    int hours, minutes;
    set_time_string(str, &hours, &minutes);

    printf("%i %i\n", hours, minutes);
}