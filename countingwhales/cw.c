#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Given a list of numbers followed by names like:

// 15 humpback
// 5 orca
// 3 humpback

// tally up the values
int name_insert (char * name, char whales[128][128]);

int main (void) {
    // make array of names.
    // 128 max length of a name
    // 128 max num whales

    int count[128];
    memset (count, 0, 128);
    char whales[128][128];
    // initialise string array.
    int i = 0;
    for (i = 0; i < 128; i++) {
        memset (whales[i], 0, 128);
    }

    int tempCount = 0;
    char tempName[128]; 

    // scanf for the D
    int read = scanf ("%d %s", &tempCount, tempName);
    while (read == 2) {
        int val = name_insert (tempName, whales);
        count[val] += tempCount;
        memset (tempName, 0, 128);
        read = scanf ("%d %s", &tempCount, tempName);
    }

    putchar ('\n');
    // print it out.
    i = 0;
    for (i = 0; i < 128; i++) {
        if (whales[i][0] != 0) {
            // printf ("%d %s\n", count[i], whales[i]);
        }
    }

    return 0;
}


int print_largest (int smaller_than, char whales[128][128], int count[128]) {
    int i = 0;
    int largest = ;
    while (i < 128) {
        if (count[i] < smaller_than && count[i]) {
            largest = i;
        }
        i++;

// given a new name, makes a new entry into the list and gives back the number
// given an existing name, gives the old number back.
int name_insert (char * name, char whales[128][128]) {

    int firstFree = 0;
    int i = 0;
    while (i < 128) {
        if (whales[i][0] == 0 && whales[i][1] == 0) {
            firstFree = i;
            break;
        }
        i++;
    }

    // perform lookup
    i = 0;
    while (i < firstFree) {
        // printf ("[%s] [%s]\n", name, whales[i]);
        if (strcmp (name, whales[i]) == 0) {
            return i;
        }
        i++;
    }

    // didn't find it so insert @ firstFree.
    strcpy (whales[firstFree], name);
    return firstFree;
}

