#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET "abcdefghijklmnopqrstuvwxyz"
// #define DEBUG 1
int letterToColumn (char c, char * alphabet)  {
    int i = 0;
    while (i < strlen (alphabet)) {
        if (c == alphabet[i]) return i;
        else i++;
    }
    return -1;
}

void finiteAutomataThatShit (int ** table, char * alphabet, char * searchString, int targetRow) {
    int currentRow = 0;
    int index = 0;
    while (index < strlen (searchString)) {
        char processLetter = searchString[index];
        int targetColumn = letterToColumn (processLetter, alphabet);
        currentRow = table[currentRow][targetColumn];
        if (currentRow == targetRow) { // we reached the end GG
            printf ("FOUND STRING ENDING AT %d\n", index);
            return;
        }
        printf ("STATE %d\n", currentRow);
        index++;
    }
    printf ("NOT FOUND\n");
    return;
}


void fillEntry (char * alphabet, char * searchString, int ** table, int row, int col) {
    if (row == 0) {
        if (alphabet[col] != searchString[0]) {
            table[row][col] = 0;
        } else {
            table[row][col] = 1;
        }
        return;
    }
    // if you're on row 4, you have 4 of the required characters + null terminator
    // add one more space for the character we're adding
    // add one for null terminator
    char * matchedString = malloc (row + 2);

    memcpy (matchedString, searchString, row);
    // memcpy should fill in stuff, up to before the "row" index
    // if we're on row 4, it means we've matched up to 4 characters,
    // add on the alphabet character at column since that is what
    // this row/col represents
    matchedString[row] = alphabet[col]; 
    matchedString[row + 1] = '\0';
#ifdef DEBUG
    printf ("newString: %s\n", matchedString);
#endif
    // now try and match matchedString with searchString, starting
    // from index 0, shifting upward, and see when we get a match
    // this will tell us which state we can revert to.
    int startingPosition = 0;
    while (startingPosition < row + 2) {
        int matchIndex = startingPosition;
        int searchStringIndex = 0;
        int mismatch = 0;
        int entered = 0;
        while (matchIndex < strlen(matchedString)) {
#ifdef DEBUG
            printf ("comparing [%c] [%c]\n", matchedString[matchIndex], searchString[searchStringIndex]);
#endif
            if (matchedString[matchIndex] != searchString[searchStringIndex]) {
                mismatch = 1;
            }
            matchIndex++; // check the pair
            searchStringIndex++;
            entered++;
        }
#ifdef DEBUG
        printf ("-\n");
#endif
        // if we get here, and mismatch is unset, we found a match
        if (mismatch == 0 && entered != 0) {
            // if it's a full match go to next row
            if (startingPosition == 0) {
#ifdef DEBUG
                printf ("full match!\n");
#endif
                table[row][col] = row+1;
            } else { // partial match meaning we're going back
                table[row][col] = startingPosition + 1;
#ifdef DEBUG
                printf ("partial match [%d]!\n", table[row][col]);
#endif
            } 
            return;
        }
        // No match, try the next startingPosition
        startingPosition++; // try starting on up
    }

    // if we get here, there was no match at all
    // return to state 0.
    table[row][col] = 0;
    return;
}

int main (void) {
    char * string = malloc (10000);
    char * alphabet = ALPHABET;
    printf ("Enter the string we're looking for: ");
    scanf ("%s", string);
    int targetLength = strlen (string);
    int alphabetLength = strlen (alphabet);
    // malloc the precompute table
    // we need targetLength rows, and ALPHABET columns
    
    // +1 for state0 (no match)
    int ** table = malloc (sizeof (int *) * (targetLength + 1));
    int foundRow = targetLength;
    int index = 0;
    while (index < targetLength) {
        table[index] = malloc (sizeof (int) * alphabetLength);
        index++;
    }

    index = 0;
    while (index < targetLength) {
        int column = 0;
        while (column < alphabetLength) {
            // fill table
            fillEntry (alphabet, string, table, index, column);
#ifdef DEBUG
            printf ("[%d][%d] => %d\n", index, column, table[index][column]);
#endif
            column++;
        }
        index++;
    }

    char * stringToLookIn = malloc (100000);
    printf ("Enter the string we're looking for it in: ");
    scanf ("%s", stringToLookIn);

    finiteAutomataThatShit (table, alphabet, stringToLookIn, foundRow);

    return EXIT_SUCCESS;
}


