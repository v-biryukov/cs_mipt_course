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


int main(int argc, char** argv)
{
    // Смотрим аргументы командной строки
    if (argc != 3)
    {
        printf("Error!\n");
        printf("To use this program: ./brightness <ppm image> <brightness change>\n");
        exit(1);
    }

    int brightness_change;
    sscanf(argv[2], "%d", &brightness_change);
    

    // Считываем
    FILE* inputfile = fopen(argv[1], "rb");
    if (inputfile == 0)
    {
        printf("Can't open the file: %s\n", argv[1]);
        exit(1);
    }
    int width, height;
    fscanf(inputfile, "P6\n%d %d\n255\n", &width, &height);
    Color* data = (Color*)malloc(sizeof(Color) * width * height);
    fread(data, sizeof(Color), height * width, inputfile);
    fclose(inputfile);


    // Меняем яркость
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // Тут нужно завести переменную типа int, так как если просто прибавлять
            // яркость к типу unsigned char, то может произойти переполнение, которое никак не получится отследить
            int red = data[i + width * j].r + brightness_change;
            if (red > 255)
                red = 255;
            else if (red < 0)
                red = 0;
            int green = data[i + width * j].g + brightness_change;
            if (green > 255)
                green = 255;
            else if (green < 0)
                green = 0;
            int blue = data[i + width * j].b + brightness_change;
            if (blue > 255)
                blue = 255;
            else if (blue < 0)
                blue = 0;
            data[i + width * j].r = red;
            data[i + width * j].g = green;
            data[i + width * j].b = blue;
        }
    }


    // Записываем
    FILE* outputfile = fopen("result.ppm", "wb");
    fprintf(outputfile, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), height * width, outputfile);
    fclose(outputfile);
    
    
    free(data);
}