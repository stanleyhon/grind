// given an array, find the smallest and largest values in the array
// do it in less than 2N comparisons.

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



