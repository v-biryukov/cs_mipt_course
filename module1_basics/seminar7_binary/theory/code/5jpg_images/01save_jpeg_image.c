#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main()
{
    int width = 400, height = 300, channels = 3;
    unsigned char* img = (unsigned char*)malloc(channels * width * height);


    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            img[channels * (j * width + i) + 0] = 80;
            img[channels * (j * width + i) + 1] = i / 2;
            img[channels * (j * width + i) + 2] = j / 2;
            
        }
    }

    int success = stbi_write_jpg("test.jpg", width, height, channels, img, 100);
    if(success == 0)
    {
        fprintf(stderr, "Error while saving image\n");
        exit(1);
    }
    
    free(img);
}