#include <stdio.h>
#include <stdlib.h>

struct color
{
    unsigned char r, g, b;
};
typedef struct color Color;


int main()
{
    int width = 600, height = 400;
    Color* data = (Color*)malloc(sizeof(Color) * width * height);

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (j < height / 3)
            {
                data[i + width * j].r = 255;
                data[i + width * j].g = 255;
                data[i + width * j].b = 255;
            }
            else if (j < 2 * height / 3)
            {
                data[i + width * j].r = 0;
                data[i + width * j].g = 57;
                data[i + width * j].b = 146;
            }
            else
            {
                data[i + width * j].r = 213;
                data[i + width * j].g = 43;
                data[i + width * j].b = 30;
            }
        }
    }

    FILE* file = fopen("flag.ppm", "wb");
    fprintf(file, "P6\n%i %i\n255\n", width, height);
    fwrite(data, sizeof(Color), height * width, file);
    fclose(file);
    
    free(data);
}