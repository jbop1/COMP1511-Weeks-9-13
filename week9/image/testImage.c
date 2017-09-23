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

    
    //Obeying newton
    destroyImage(i);

    printf("Every test succeeded\n");

    return EXIT_SUCCESS;
}
