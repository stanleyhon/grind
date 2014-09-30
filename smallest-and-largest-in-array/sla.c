// given an array, find the smallest and largest values in the array
// do it in less than 2N comparisons.
// take elements out of the array two at a time
// compare them with eachother,
// then compare the lower one with min to see if it's the new min
// and compare the larger one with max to see if it's the new max.

// this is O (2N/3)~ since doing the extra comparison of the pair, saves you comparing the larger of the two with min
// and the smaller of the two with max.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// must be divisible by 2 for simplicity sake
#define SIZE 100000

void work (int * array) {
    int min;
    int firstRun = 1;
    int max;
    int idx = 0;
    while (idx < SIZE - 1) { // minus one, since we are working on pairs
        if (array[idx] >= array[idx + 1]) {
            if (firstRun == 1) { // firstrun, just take them as your values
                firstRun = 0;
                max = array[idx];
                min = array[idx+1];
            } else {
                if (array[idx] > max) {
                    max = array[idx];
                }
                if (array[idx + 1] < min) {
                    min = array[idx + 1];
                }
            }
        } else { // so array[idx] is smaller
            if (firstRun == 1) { // firstrun, just take em as your min max
                firstRun = 0;
                min = array[idx];
                max = array[idx + 1];
            } else {
                if (array[idx] < min) {
                    min = array[idx];
                }
                if (array[idx + 1] > max) {
                    max = array[idx + 1];
                }
            }
        }
        idx = idx + 2;
    }
    
    printf ("MAX %d MIN %d\n", max, min);
    return;
}


int main (void) {
    int * array = malloc (sizeof (int) * SIZE);
    int idx = 0;
    srand (time (NULL));
    while (idx < SIZE) {
        array[idx] = rand ();
        printf ("%d\n", array[idx]);
        idx++;
    }

    work (array);

    return EXIT_SUCCESS;
}



