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
    if (img img == null) {
        err(EXIT_FAILURE, "calloc, failed");
    }


    img->width = width;
    img->height = height;
    
    pixel **new;

    new = calloc (height, sizeof (pixel *));
    int i = 0;

    while (i < height) {
        new[i] = calloc (width, sizeof (pixel));
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

int main (int argc, char *argv[]) {
    Image img = newImage(1000, 1000);
    
    print (img);
    
    unsigned char *buf;
    int size = imageAsBMP (img, &buf);
    fwrite (buf, sizeof (unsigned char), size, stdout);

    free(buf);

    destroyImage(img);

    printf("Happy days\n");

    return EXIT_SUCCESS;
}
