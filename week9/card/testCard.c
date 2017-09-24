#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Card.h"

int main (int argc, char *argv[]) {
    
    color col;
    suit suit;
    unsigned int number;
    
    printf("Please enter a color, suit, and number\n");
    scanf("%d %d %x", &col, &suit, &number);

    Card new = newCard(number, col, suit);
    
    assert(new != NULL);

    assert (cardSuit (new) == suit);
    assert (cardColor (new) == col);
    assert (cardNumber (new) == number);

    destroyCard(new);

    printf("Happy Days\n");
    
    return EXIT_SUCCESS;

}
