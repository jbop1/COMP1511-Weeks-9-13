// The playing card implementation.
//
// This is an implementation of the Card ADT, which represents a single
// playing card in the game of Final Card-Down.
//
// By ... (z0000000)
//    ... (z0000000)
// Written on 2017-09-??
// Tutor (dayHH-lab)

#include <stdlib.h>
#include <err.h>

#include "Card.h"

typedef struct _card {
    color color;
    suit suit;
    char number; 
} card;

// Create a new card.
// These values can only be set at creation time.
// The number should be between 0x0 and 0xF.
Card newCard(char number, color color, suit suit) {
    if (number < 0x0 || number > 0xF) {
        errx (EXIT_FAILURE, "Card number out of range");
    }
    
    Card newCard = calloc (1, sizeof (card));
    
    if (newCard == NULL) {
        errx (EXIT_FAILURE, "Calloc failed");
    }

    newCard->number = number;
    newCard->color = color;
    newCard->suit = suit;
    
    return newCard;
}

// Destroy an existing card.
void destroyCard(Card card) {
    free (card);
}

// Get the card suit (HEARTS, DIAMONDS, etc).
suit cardSuit(Card card) {
    return card->suit; 
}

// Get the card number (0x0 through 0xF).
char cardNumber(Card card) {
    return card->number;
}

// Get the card's color (RED, BLUE, etc).
color cardColor(Card card) {
    return card->color;
}
