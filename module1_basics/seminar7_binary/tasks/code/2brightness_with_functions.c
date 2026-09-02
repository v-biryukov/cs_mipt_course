#include <stdio.h>
#include <stdlib.h>

// To compile:
// gcc -std=c99 -o brightness brightness.c

// To run:
// ./brightness images/emir.ppm -70

struct color
{
    unsigned char r, g, b;
};
typedef struct color Color;


Color* load_image(char* filename, int* pwidth, int* pheight)
{
    FILE* inputfile = fopen(filename, "rb");
    if (inputfile == 0)
    {
        printf("Can't open the file: %s\n", filename);
        exit(1);
    }
    fscanf(inputfile, "P6\n%d %d\n255\n", pwidth, pheight);
    Color* data = (Color*)malloc(sizeof(Color) * (*pwidth) * (*pheight));
    fread(data, sizeof(Color), (*pwidth) * (*pheight), inputfile);
    fclose(inputfile);
    return data;
}

void save_image(char* filename, Color* data, int width, int height)
{
    FILE* outputfile = fopen(filename, "wb");
    fprintf(outputfile, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), height * width, outputfile);
    fclose(outputfile);
}

void increase_brightness(Color* data, int width, int height, int addiational_brightness)
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int red = data[i + width * j].r + addiational_brightness;
            if (red > 255)
                red = 255;
            else if (red < 0)
                red = 0;
            int green = data[i + width * j].g + addiational_brightness;
            if (green > 255)
                green = 255;
            else if (green < 0)
                green = 0;
            int blue = data[i + width * j].b + addiational_brightness;
            if (blue > 255)
                blue = 255;
            else if (blue < 0)
                blue = 0;
            data[i + width * j].r = red;
            data[i + width * j].g = green;
            data[i + width * j].b = blue;
        }
    }
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Error!\n");
        printf("To use this program: ./brightness <ppm image> <brightness change>\n");
        exit(1);
    }
    int brightness_change;
    sscanf(argv[2], "%d", &brightness_change);
    
    int width, height;
    Color* data = load_image(argv[1], &width, &height);

    increase_brightness(data, width, height, brightness_change);
    save_image("result.ppm", data, width, height);
    
    free(data);
}