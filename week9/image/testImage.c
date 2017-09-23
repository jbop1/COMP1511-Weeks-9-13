// Black box tests for Image.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Image.h"

int main (int argc, char *argv[]) {
    unsigned int width = 100;
    unsigned int height = 100;

    Image i = newImage(width, height); 
    
    //Check width, and height
    assert(imageGetWidth(i) == width);
    assert(imageGetHeight(i) == height);


    //Check

    //Check
    generateImage(img);
    
    //Obeying newton
    destroyImage(i);

    printf("Every test succeeded\n");

    return EXIT_SUCCESS;
}


static void genereateImage(Image i) {
    
    unsigned char *buf;
    int size = imageAsBMP (i, &buf);
    fwrite (buf, sizeof (unsigned char), size, stdout);

    free(buf);

}

static void print (Image img) {
    int i = 0;
    int j = 0;
    
    pixel col = {
        .red = 0,
        .green = 0,
        .blue = 255
    };
    
    while (i < img->height) {
        while (j < img->width) {
            point p = {
                .x = j,
                .y = i
            };
            
            imageSetPixel(img, p, col);         

            //pixel pix = imageGetPixel(img, p);

            //printf("x: %d, y: %d\n", j, i); 
            //printf("red: %d, green: %d, blue: %d \n", pix.red, pix.green, pix.blue); 

            j++;
        }

        j = 0;
        i++;
    }
}

