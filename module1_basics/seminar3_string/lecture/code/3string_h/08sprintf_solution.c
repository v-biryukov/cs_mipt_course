#include <stdio.h>

void get_time_string(int hours, int minutes, char str[])
{
    sprintf(str, "%02i:%02i", hours, minutes);
}

int main() 
{
    char str[20];
    get_time_string(12, 5, str);

    printf("%s\n", str);
}