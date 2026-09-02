#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define M_PI 3.14159265358

struct color
{
    unsigned char r, g, b;
};
typedef struct color Color;

const Color White = {255, 255, 255};
const Color Black = {0, 0, 0};


// Функция, которая рисует линию от (x0, y0) до (x1, y1) цвета c на холте data
void draw_line(Color* data, int width, int height, int x0, int y0, int x1, int y1, Color c)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int ysign = y1 > y0 ? 1 : -1;
    int xsign = x1 > x0 ? 1 : -1;
    int error = (dx > dy ? dx : -dy)/2;

    if (dx >= dy)
    {
        int y = y0;
        for (int x = x0 ; x != x1; x += xsign)
        {
            data[x + width * y] = c;
            error += dy;
            if (error >= dx)
            {
                y += ysign;
                error -= dx;
            }
        }
    }
    else
    {
        int x = x0;
        for (int y = y0 ; y != y1; y += ysign)
        {
            data[x + width * y] = c;
            error += dx;
            if (error >= dy)
            {
                x += xsign;
                error -= dy;
            }
        }
    }

}

int main()
{
    int width = 500, height = 500;
    Color* data = (Color*)malloc(sizeof(Color) * width * height);

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            data[i + width * j] = Black;
        }
    }

    // Рисуем линии из точки (250, 250) во все стороны
    int length = 200;
    int number_of_lines = 80;
    for (int i = 0; i < number_of_lines; ++i)
    {
        float angle = i * 2 * M_PI / number_of_lines;
        
        int x = 250 + length * cos(angle);
        int y = 250 + length * sin(angle);

        // Color c = {255 * fabs(sin(3 * angle)), 255 * fabs(sin(5 * angle)), 255 * fabs(sin(11 * angle))};
        draw_line(data, width, height, 250, 250, x, y, White);
    }

    FILE* file = fopen("lines.ppm", "wb");
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), height * width, file);
    fclose(file);
    
    free(data);
}