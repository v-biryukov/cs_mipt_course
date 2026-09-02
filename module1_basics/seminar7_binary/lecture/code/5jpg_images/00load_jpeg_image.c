#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
    int width, height, channels;
    unsigned char* img = stbi_load("russian_peasants.jpg", &width, &height, &channels, 0);
    
    if(img == NULL)
    {
        fprintf(stderr, "Error while loading image\n");
        exit(1);
    }

    printf("%i\n", width);
    printf("%i\n", height);
    printf("%i\n", channels);

    for (int i = 0; i < 100; ++i)
    {
        printf("%x\n", (int)img[i]);
    }
    printf("\n");

    stbi_image_free(img); 
}