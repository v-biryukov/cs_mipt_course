#include <stdio.h>

int main(int argc, char** argv)
{
    int result = 0;

    for (int i = 1; i < argc; ++i)
    {
        int temp;
        sscanf(argv[i], "%i", &temp);
        result += temp;
    }

    printf("%i\n", result);
}
