#include <stdio.h>
#include <stdlib.h>

struct color
{
    unsigned char r, g, b;
};
typedef struct color Color;


int main()
{
    // Данные пикселей в картинке 3x2
    Color data[6] = {{109, 53, 35}, {116, 116, 94}, {52, 72, 49}, {40, 41, 95}, {43, 124, 53}, {58, 34, 60}};


    // Сохраняем картинку в текстовом формате
    FILE* ft = fopen("tiny_text.ppm", "w");
    fprintf(ft, "P3\n3 2\n255\n");
    for (int i = 0; i < 6; i++) 
    {
        fprintf(ft, "%i %i %i\n", data[i].r, data[i].g, data[i].b);
    }
    fclose(ft);


    // Сохраняем картинку в бинарном формате
    FILE* fb = fopen("tiny_binary.ppm", "wb");
    fprintf(fb, "P6\n%i %i\n255\n", 3, 2);
    fwrite(data, sizeof(Color), 6, fb);
    fclose(fb);
}