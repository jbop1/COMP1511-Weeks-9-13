#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>

#include "Image.h"

#define TRUE 1
#define FALSE (!TRUE)

typedef struct _image {
    unsigned int width;
    unsigned int height;
    pixel **data;
} image;

Image newImage (unsigned int width, unsigned int height) {
    Image img = calloc (1, sizeof (image));
    if (img == NULL) {
        errx(EXIT_FAILURE, "calloc, failed");
    }

    img->width = width;
    img->height = height;
    
    pixel **new;

    new = calloc (height, sizeof (pixel *));
    
    if (new == NULL) {
        errx(EXIT_FAILURE, "calloc failed");
    }
    
    int i = 0;

    while (i < height) {
        new[i] = calloc (width, sizeof (pixel));
        
        if (new[i] == NULL) {
            errx(EXIT_FAILURE, "calloc failed");
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

int crossProduct (point a, point b) {
    return (a.x * b.y) - (a.y * b.x);
}

int dotProduct (point a, point b) {
    return a.x * b.x + a.y * b.y;
}

point produceVector (point a, point b) {
    point vector = {
        .x = b.x - a.x,
        .y = b.y - a.y
    };

    return vector;
}

int getModulusSquared (point p) {
    return (p.x * p.x) + (p.y * p.y);
}

int assertLine (point ba, point ca) {
    int onLine = TRUE;

    if (abs(crossProduct(ba, ca)) != 0) {
        onLine = FALSE;
    }

    if (dotProduct (ba, ca) < 0) {
        onLine = FALSE;
    }

    if (getModulusSquared (ba) < dotProduct(ba, ca)) {
        onLine = FALSE;
    }

    return onLine;
}

void imageDrawLine (Image i, pixel color, point start, point end) {

    unsigned int width = imageGetWidth (i);
    unsigned int height = imageGetHeight (i);
    
    point startToEnd = produceVector (end, start);

    int w = 0;
    int h = 0;

    while (h < height) {
        while (w < width) {
            point currentPoint = {
                .x = w,
                .y = h
            };

            point ca = produceVector (start, currentPoint);

            if (assertLine(startToEnd, ca)) {
                imageSetPixel(i, currentPoint, color);
            }

            w++;
        }
        
        h++;
        w = 0;
    }
}

void imageDrawRectangle (
    Image i, pixel color, point bottomLeft, point topRight) {
   

    point p1 = {
        .x = bottomLeft.x,
        .y = topRight.y
    };

    point p2 = {
        .x = topRight.x,
        .y = topRight.y
    };

    point p3 = {
        .x = topRight.x,
        .y = bottomLeft.y
    };

    point p4 = {
        .x = bottomLeft.x,
        .y = bottomLeft.y
    };

    point top = produceVector (p1, p2);
    point right = produceVector (p2, p3);
    point bot = produceVector (p4, p3);
    point left = produceVector (p1, p4);
        
    unsigned int width = imageGetWidth (i);
    unsigned int height = imageGetHeight (i);
    
    int w = 0;
    int h = 0;

    while (h < height) {
        while (w < width) {
            point currentPoint = {
                .x = w,
                .y = h
            };
            
            int printPix = TRUE;

            point p1cp = produceVector(p1, currentPoint);
            point p2cp = produceVector(p2, currentPoint);
            point p3cp = produceVector(p3, currentPoint);
            point p4cp = produceVector(p4, currentPoint);

            if (crossProduct(top, p1cp) > 0) {
                printPix = FALSE;
            }

            if (crossProduct(right, p2cp) > 0) {
                printPix = FALSE;
            }
            
            if (crossProduct(bot, p4cp) < 0) {
                printPix = FALSE;
            }

            if (crossProduct(left, p1cp) < 0) {
                printPix = FALSE;
            }

            if (printPix) {
                imageSetPixel (i, currentPoint, color);
            }


            w++;
        }
        
        h++;
        w = 0;
    }



}

void imageDrawCircle (
    Image i, pixel color, point centre, unsigned int radius) {
    
    unsigned int width = imageGetWidth (i);
    unsigned int height = imageGetHeight (i);

    int w = 0;
    int h = 0;

    while (h < height) {
        while (w < width) {
            double rad = (w - centre.x) * (w - centre.x) + (h - centre.y) * (h - centre.y);
            if (rad < pow (radius, 2)) {

                point p = {
                    .x = w,
                    .y = h
                };

                imageSetPixel (i, p, color);
            }
           
            w++;
        }

        w = 0;
        h++;
    }
}
