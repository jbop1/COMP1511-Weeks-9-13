#include <stdio.h>
#include <stdlib.h>

#include "Image.h"

typedef struct _image {
    unsigned int width;
    unsigned int height;
    pixel **data;
} image;

Image newImage (unsigned int width, unsigned int height) {
    Image img = calloc (1, sizeof (image));
    if (img == null) {
        errx(EXIT_FAILURE, "calloc, failed");
    }


    img->width = width;
    img->height = height;
    
    pixel **new;

    new = calloc (height, sizeof (pixel *));
    
    if (new == null) {
        errx(EXIT_FAILURE, "calloc failed");
    }
    
    int i = 0;

    while (i < height) {
        new[i] = calloc (width, sizeof (pixel));
        
        if (new[i] == null) {
            errx(EXIT_FAILURE, "calloc failed")'
        }
        
        i++;
    }

    img->data = new;

    return img;
}

void destroyImage (Image i) {
    free (i);
}

unsigned int imageGetWidth (Image i) {
    return i->width;   
}

unsigned int imageGetHeight (Image i) {
    return i->height;
}

pixel imageGetPixel (Image i, point p) {
    return i->data[p.y][p.x];
}

void imageSetPixel (Image i, point p, pixel color) {
    i->data[p.y][p.x] = color;
}
