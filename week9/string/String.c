// Creates a string ADT
// Jasvir Boparoy (z5165068)
// Jack Gifford (z5160408)
// 2017-09-22

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>
#include "String.h"

#define TRUE 0
#define FALSE !(TRUE)

//Prototype
static void copyArrayContent (String s, char *charArray);

typedef struct _string {
    char *content;
    int length;
    
} string;


// Create a new `String`, from a C-style null-terminated array of
// characters.
String newString (char *str) {
    String newString = calloc(1, sizeof(string));
    assert(newString != NULL);
    
    copyArrayContent(newString, str);
    newString->length = stringLength(newString);
    
    return newString;
}

static void copyArrayContent (String s, char *charArray) {
    int length = 0;
    while (charArray[length] != '\0') {
        length++;
    }

    s->content = calloc(length + 1, sizeof(char));
    
    int i = 0;
    while (i < length + 1) {
        s->content[i] = charArray[i];
        i++;
    }
        
}

// Release all resources associated with a `String`.
void destroyString (String s) {
    free(s);
}

// Get the length of a `String`.
int stringLength (String s) {
    int i = 0;
    while (s->content[i] != '\0') {
        i++;
    }
    
    return i;
}

// Make a (mutable) copy of a `String`.
String stringClone (String s) {
    String sCopy = newString(s->content);
    
    return sCopy;
}

// Given a `String`, and an index in the `String`, return the
// character at that index.
char stringAt (String s, int index) {
    
    if (index > s->length) {
        err(EXIT_FAILURE, "Index out of range");
    }

    return s->content[index];
}

// Given a `String`, and a character to look for in the `String`,
// return either the index of the character, or `-1` if the character
// could not be found in the `String`.
int stringFindChar (String s, char find) {
    int indexChar = 0;
    
    while (indexChar < s->length && s->content[indexChar] != find) {
        indexChar++;
    }
    
    if (indexChar == s->length) {
        indexChar = -1;
    }
    
    return indexChar;
}

// Are two `String`s equal?
int stringsEqual (String s1, String s2) {
    int stringsAreEqual = TRUE;
    
    if (s1->length == s2->length) {
        int i = 0;
        while (s1->content[i] != '\0') {
            if (s1->content[i] != s2->content[i]) {
                stringsAreEqual = FALSE;
            }
            
            i++;
        }
    } else {
        stringsAreEqual = FALSE;
    }
    
    return stringsAreEqual;
}

// Given two `String`s, concatenates them into a new `String`.
String stringConcat (String s1, String s2) {
    int s1Length = stringLength(s1);
    int s2Length = stringLength(s2);
    int newLength = (s1Length + s2Length) + 1;
    
    char *concatStr = calloc(newLength, sizeof(char));
    
    int concatStrIndex = 0;
    while (concatStrIndex < s1Length) {
        concatStr[concatStrIndex] = s1->content[concatStrIndex];
        concatStrIndex++;
    }
    
    int s2Index = 0;
    while (s2Index < s2Length + 1) {
        concatStr[concatStrIndex] = s2->content[s2Index];
        concatStrIndex++;
        s2Index++;
    }
    
    String newStr = newString(concatStr);
    
    free(concatStr);
    
    return newStr;      
}

int main (int argc, char *argv[]) {
    char strContent[] = "hello";
    
    //Testing constructor
    String str = newString(strContent);

    printf("Expected: hello. Actual: %s.\n", str->content);
    printf("Expected: 5. Actual: %d.\n", str->length);
    
    //Testing clone func
    String strCloned = stringClone(str);
    
    printf("Expected: hello. Actual: %s.\n", strCloned->content);
    printf("Expected: 5. Actual: %d.\n", strCloned->length);
    
    // Testing stringAt func
    char value = stringAt(str, 3);
    printf("Expected: l. Actual: %c.\n", value);
    printf("Expected: \\0. Actual: %c.\n", stringAt(str, 5));
    
    //Should throw an exception
    //stringAt(str, 6);
    
    //Find character
    printf("Expected: 2. Actual: %d.\n", stringFindChar(str, 'l'));
    printf("Expected: -1. Actual: %d.\n", stringFindChar(str, 'a'));
    printf("Expected: 0. Actual: %d.\n", stringFindChar(str, 'h'));
    
    // Tests stringsEqual
    
    printf("Expected: 0. Actual: %d.\n", stringsEqual(str, strCloned));
    
    char sameLength[] = "HELLO";
    String same = newString(sameLength);
    
    char diffLength[] = "hellohello";
    String diff = newString(diffLength);
    
    printf("Expected: 1. Actual: %d.\n", stringsEqual(str, diff));
    printf("Expected: 1. Actual: %d.\n", stringsEqual(str, same));    
    
    // Tests stringConcat
    String concat = stringConcat(str, str);
    printf("Expected: hellohello. Actual: %s.\n", concat->content);
    
    destroyString(str);
    destroyString(strCloned);
    destroyString(same);
    destroyString(diff);
    destroyString(concat);
    
    return EXIT_SUCCESS;
}
