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

    //Check getPixel
    pixel startingCol {
        .red = 0,
        .green = 0,
        .blue = 0
    };
    
    bulkSet(img, startingCol);
    
    //Check setPixel
    pixel col = {
        .red = 0,
        .green = 0,
        .blue = 255
    };
    
    bulkSet(img, col);
    print(img, col);

    //Check image generates properly
    generateImage(img);
    
    //Obeying newton
    destroyImage(i);

    printf("Every test succeeded\n");

    return EXIT_SUCCESS;
}


static void generateImage (Image i) {
    
    unsigned char *buf;
    int size = imageAsBMP (i, &buf);
    fwrite (buf, sizeof (unsigned char), size, stdout);

    free(buf);

}

static void bulkGet (Image img, pixel expectedColor) {
    int i = 0;
    int j = 0;
    
    while (i < img->height) {
        while (j < img->width) {
            point p = {
                .x = j,
                .y = i
            };
            
            pixel pix = imageGetPixel(img, p);

            assert(expectedColor.red == pix.red);
            assert(expectedColor.green == pix.green);
            assert(expectedColor.blue == pix.blue);

            j++;
        }

        j = 0;
        i++;
    }
}

static void bulkSet (Image img, pixel newColor) {
    int i = 0;
    int j = 0;
    
    while (i < img->height) {
        while (j < img->width) {
            point p = {
                .x = j,
                .y = i
            };
            
            imageSetPixel (img, p, newColor);
            j++;
        }

        j = 0;
        i++;
    }
}
