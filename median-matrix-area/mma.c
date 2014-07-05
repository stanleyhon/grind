// Problem definition is as follows.
// You are given an array of 1s and 0s.
// An area is defined as a block of 1s connected by up down left or rights
// (i.e. not diagonal).

// Find the median area (middle value when list of all areas sorted).

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define FREQUENCY 65
#define DIMENSIONS 40

int partition (int * values, int low, int high) {
    assert (low <= high);
    assert (low >= 0 && low < DIMENSIONS*DIMENSIONS);
    assert (high >= 0 && high < DIMENSIONS*DIMENSIONS);
    // choose low as the pivot.
    int pivotValue = values[low];
    int leftHand = low + 1;
    while (leftHand <= high) {
        if (values[leftHand] <= pivotValue) {
            leftHand++;
        } else {
            // find something up above to swap it with
            int swapCandidate = leftHand + 1;
            while (swapCandidate <= high) {
                if (values[swapCandidate] <= pivotValue) {
                    // found a good swap candidate, swap.
                    int temp = values[swapCandidate];
                    values[swapCandidate] = values[leftHand];
                    values[leftHand] = temp;
                    break;
                } 
                
                // Not a good swap, keep looking
                swapCandidate++;
            }

            // We finished the candidate swap or we ran out of things to compare.
            leftHand = swapCandidate;
            // There are a few cases here:
            // 1. A swap occurred, and leftHand indicates the element we swapped. 
            // 2. No swap was possible because we ran out of room
        }
    }

    // Figure out where to put the pivot.
    int index = low;
    while (index < high) {
        if (values[index] <= pivotValue && values[index+1] > pivotValue) {
            int temp = values[index];
            values[index] = values[low];
            values[low] = temp;
            break;
        } else if (index == high - 1) { // just put it at the end
            int temp = values[high];
            values[high] = values[low];
            values[low] = temp;
        }
        index++;
    }

    assert (index <= high && index >= low);

    return index;
}


int quickselect (int * values, int maxIndex) {
    int wantedIndex = maxIndex / 2;
    printf ("Total %d\n", maxIndex);
    printf ("Looking for %d\n", wantedIndex); 
    int low = 0;
    int high = maxIndex;
    int pivot = partition (values, low, high);
    
    while (pivot != wantedIndex) {
        // which half of the pivot is it in?
        if (pivot > wantedIndex) { // left half
            high = pivot - 1;
            pivot = partition (values, low, high);
        } else if (pivot < wantedIndex) { // right half
            low = pivot + 1;
            pivot = partition (values, low, high);
        }
    }

    // we found the pivot!
    return values[pivot];
}

int find_region (int ** matrix, int col, int row) {
    if (col >= DIMENSIONS || row >= DIMENSIONS || row < 0 || col < 0) return 0;
    int total;
    if (matrix[col][row] != 1) {
        return 0; // we aren't part of the area.
    } else {
        // mark ourselves as seen
        matrix[col][row] = 2;
        total = 1; // Count ourselves
        // Up?
        total += find_region (matrix, col, row + 1);
        // Down?
        total += find_region (matrix, col, row - 1);
        // Left?
        total += find_region (matrix, col - 1, row);
        // Right?
        total += find_region (matrix, col + 1, row);
    }
    return total;
}
        

void parse_array (int ** matrix, int * array, int * nextFree) {
    int col = 0;
    while (col < DIMENSIONS) {
        int row = 0;
        while (row < DIMENSIONS) {
            if (matrix[col][row] == 1) {
                int area = find_region (matrix, col, row);
                array[*nextFree] = area;
                *nextFree = *nextFree + 1;
            }
            row++;
        }
        col++;
    }

    return;
}

void show_array (int ** matrix) {
    int col = 0;
    while (col < DIMENSIONS) {
        int row = 0;
        while (row < DIMENSIONS) {
            printf ("%d ", matrix[col][row]);
            row++;
        }
        printf("\n");
        col++;
    }
    return;
}

int main (void) {
    // Read the array in first
    int ** matrix = malloc (sizeof (int*) * DIMENSIONS);

    int index = 0;
    while (index < DIMENSIONS) {
        matrix[index] = malloc (sizeof (int) * DIMENSIONS);
        index++;
    }

    srand (time(NULL));

    int col = 0;
    while (col < DIMENSIONS) {
        int row = 0;
        while (row < DIMENSIONS) {
            int value = rand() % 100;
            if (value < 100-FREQUENCY) {
                matrix[col][row] = 0;
            } else {
                matrix[col][row] = 1;
            }
            row++;
        }
        col++;
   }

    // Show the matrix
    show_array (matrix);

    // Keep track of values in an array
    int nextFree = 0;
    int * areas = malloc (sizeof (int) * DIMENSIONS * DIMENSIONS);

    // Parse matrix
    parse_array (matrix, areas, &nextFree);

    // See what values we come up with
    index = 0;
    printf ("AREAS: ");
    while (index < nextFree) {
        printf ("%d ", areas[index]);
        index++;
    }
    printf("\n");

    // Perform quick select for median.
    printf ("Median Area: %d\n", quickselect (areas, nextFree - 1));

    return EXIT_SUCCESS;
}
