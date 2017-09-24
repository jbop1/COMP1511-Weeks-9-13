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
    
    // Jasvir's tests
    
    // TEST 1 for in range values
    color newColor = RED;
    suit newSuit = HEARTS;
    char newNumber = 12;
    Card c = newCard(newNumber, newColor, newSuit);
    assert (c != NULL);

    // test cardSuit
    printf("Expected: HEARTS, Received: %d\n", cardSuit(c));

    // test cardNumber
    printf("Expected: 0xC, Received: %#X\n", cardNumber(c));

    // test cardColor
    printf("Expected: 0, Received: %d\n", cardColor(c));

    // TEST 2 for out of range suit
    color newColor1 = RED;
    suit newSuit1 = 8;
    char newNumber1 = 12;
    Card cardNew = newCard(newNumber1, newColor1, newSuit1);
    assert (c != NULL);

    // test cardSuit (SHOULD FAIL HERE)
    printf("Expected: 8, Received: %d\n", cardSuit(cardNew));

    // test cardNumber
    printf("Expected: 16, Received: %#X\n", cardNumber(cardNew));

    // test cardColor
    printf("Expected: 6, Received: %d\n", cardColor(cardNew));

    // TEST 3 for out of range number
    newColor1 = RED;
    newSuit1 = DIAMONDS;
    newNumber1 = 21;
    cardNew = newCard(newNumber1, newColor1, newSuit1);
    assert (c != NULL);

    // test cardSuit
    printf("Expected: 1, Received: %d\n", cardSuit(cardNew));

    // test cardNumber (SHOULD FAIL HERE)
    printf("Expected: 21, Received: %#X\n", cardNumber(cardNew));

    // test cardColor
    printf("Expected: 0, Received: %d\n", cardColor(cardNew));

    // TEST 4 for out of range color
    newColor1 = 9;
    newSuit1 = DIAMONDS;
    newNumber1 = 12;
    cardNew = newCard(newNumber1, newColor1, newSuit1);
    assert (c != NULL);

    // test cardSuit
    printf("Expected: 1, Received: %d\n", cardSuit(cardNew));

    // test cardNumber (SHOULD FAIL HERE)
    printf("Expected: 12, Received: %#X\n", cardNumber(cardNew));

    // test cardColor
    printf("Expected: 9, Received: %d\n", cardColor(cardNew));
    
    destroyCard(c);
    destroyCard(cardNew);
    
    return EXIT_SUCCESS;

}
