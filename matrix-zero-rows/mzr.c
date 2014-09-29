// Given a matrix with some zeros, for each zero, zero the entire
// row and column of the zero value.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 10
void work (int ** matrix);
void printMatrix (int ** matrix);

int main (void) {
    int ** matrix = malloc (sizeof (int *) * SIZE);
    int idx = 0;
    while (idx < SIZE) {
        matrix[idx] = malloc (sizeof (int) * SIZE);
        idx++;
    }

    srand (time (NULL));

    idx = 0;
    while (idx < SIZE) {
        int ridx = 0;
        while (ridx < SIZE) {
            matrix[idx][ridx] = 1 + rand () % 10;
            ridx++;
        }
        idx++;
    }

    // now set some to zero
    int randX = rand () % SIZE;
    int randY = rand () % SIZE;
    matrix[randX][randY] = 0;
    randX = rand () % SIZE;
    randY = rand () % SIZE;
    matrix[randX][randY] = 0;
    randX = rand () % SIZE;
    randY = rand () % SIZE;
    matrix[randX][randY] = 0;

    // now call our function it
    printMatrix (matrix);
    work (matrix);
    printMatrix (matrix);

    return EXIT_SUCCESS;
}

void printMatrix (int ** matrix) {
    int idx = 0;
    while (idx < SIZE) {
        int ridx = 0;
        while (ridx < SIZE) {
            if (matrix[idx][ridx] != 0) {
                printf ("%02d ", matrix[idx][ridx]);
            } else {
                printf ("XX ");
            }
            ridx++;
        }
        printf ("\n");
        idx++;
    }
    printf ("\n\n\n");
    return;
}

void work (int ** matrix) {
    int * zeroRows = malloc (sizeof (int) * SIZE);
    int * zeroColumns = malloc (sizeof (int) * SIZE);

    memset (zeroRows, 0, sizeof (int) * SIZE);
    memset (zeroColumns, 0, sizeof (int) * SIZE);

    int idx = 0;
    while (idx < SIZE) {
        int ridx = 0;
        while (ridx < SIZE) {
            if (matrix[idx][ridx] == 0) {
                zeroRows[idx] = 1;
                zeroColumns[ridx] = 1;
            }
            ridx++;
        }
        idx++;
    }

    // now zero those rows and columns
    idx = 0;
    while (idx < SIZE) {
        if (zeroRows[idx] == 1) { // that row is zero, set that row to zero
            int zeroIdx = 0;
            while (zeroIdx < SIZE) {
                matrix[idx][zeroIdx] = 0;
                zeroIdx++;
            }
        }
        idx++;
    }

    idx = 0;
    while (idx < SIZE) {
        if (zeroColumns[idx] == 1) {
            int zeroIdx = 0;
            while (zeroIdx < SIZE) {
                matrix[zeroIdx][idx] = 0;
                zeroIdx++;
            }
        }
        idx++;
    }
    
    return;
}
