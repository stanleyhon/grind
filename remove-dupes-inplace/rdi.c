#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void removeDupes (int * array);

int main (void) {
    int * array = malloc (sizeof (int) * 100);

    srand (time (NULL));

    int idx = 0;
    while (idx < 100) {
        array[idx] = rand () % 30;
        idx++;
    }
    
    idx = 0;
    while (idx < 100) {
        printf ("%d ", array[idx]);
        idx++;
    }
    printf ("\n");
    printf ("\n");

    removeDupes (array);

    idx = 0;
    while (idx < 100) {
        printf ("%d ", array[idx]);
        idx++;
    }

    printf ("\n");

    return EXIT_SUCCESS;
}

void removeDupes (int * array) {
    int idx = 0 ;
    while (idx < 100) {
        if (array[idx] == -1) {
            idx++;
            continue;
        }
        int val = array[idx];
        int innerIdx = idx + 1;
        while (innerIdx < 100) {
            if (array[innerIdx] == val) {
                array[innerIdx] = -1;
            }
            innerIdx++;
        }
        idx++;
    }
    return;
}

