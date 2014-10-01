// Given an array of length N, contains all values from 1 to N+1.
// Find the missing integer in < O(n log(n)) & minimal space 
// i.e. not an array of size N.

// proposed solution, use an array of 32bit integers as
// an extended bitfield.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define N 1000

int main (void) {
    int * array = malloc (sizeof (int) * N);
    memset (array, 0, N * sizeof (int));
    int setValue = 1; // this goes up until N
    srand (time (NULL));
    while (setValue <= N) {
        int targetIndex = rand () % N;
        if (array[targetIndex] == 0) {
            array[targetIndex] = setValue;
            setValue++;
        } else {
            continue; // re-random index.
        }
    }

    // now pick a random one and set it to N+1
    int targetIndex = rand () % N;
    array[targetIndex] = N+1;

    // print the array
    int idx = 0;
    while (idx < N) {
        printf ("%d\n", array[idx]);
        idx++;
    }
    printf ("\n");

    unsigned int fieldsNeeded = (N / 32) + 1;
    unsigned int * bitfield = malloc (sizeof (unsigned int) * fieldsNeeded);
    memset (bitfield, 0xFFFFFFFF, sizeof (unsigned int) * fieldsNeeded);

    idx = 0;
    while (idx < N) {
        int value = array[idx];
        // figure out which bitfield this goes in.
        int fieldNumber = value / 32; // since it's floored, this should work
        // figure out the position in the bitfield
        int position = value % 32;
        // unset that bit.
        unsigned int mask = ~(1 << position); // a mask with everything set except the "position"-th bit
        // apply the mask using AND so that the unset bit guaranteed unset
        bitfield[fieldNumber] = bitfield[fieldNumber] & mask;
        idx++; // do the next thing in the array
   }

    idx = 0;
    while (idx < fieldsNeeded) {
        printf ("%x ", bitfield[idx]);
        idx++;
    }
    bitfield[0] = bitfield[0] & ~(1); // unset the first bit

    // now we should end up with almost the entire bitfield unset except one bit. find it
    int currentField = 0;
    while (currentField < fieldsNeeded) {
        if (bitfield[currentField] == 0) {
            currentField++;
        } else {
            // found it! figure out which position.
            int shiftPosition = 0;
            while ((bitfield[currentField] & (1 << shiftPosition)) == 0) {
                shiftPosition++;
            }

            // at this point, shiftPosition will be where our bit is. work out what position is this
            int overallPosition = (currentField * 32) + shiftPosition;

            printf ("The missing number is %d\n", overallPosition);
            break;
        }
    }

    return EXIT_SUCCESS;
}
