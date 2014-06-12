// choose leftmost as pivot
// start from left and right
// when both left and right violate rule, swap
// crossover is pivot position.
// recurse on each half.
// ggwp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_SIZE 60000

int array[MAX_SIZE];

int partition (int left, int right) {
    assert (left < right);
    assert (array != NULL);
    int pivot = array[left];
    //printf ("select pivot is %d\n", pivot);
    int leftIdx = left;
    int rightIdx = right;

    while (leftIdx < rightIdx) {
        while (array[leftIdx] <= pivot && leftIdx < right) {
            leftIdx++;
        }
        while (array[rightIdx] > pivot && rightIdx > 0) {
            rightIdx--;
        }
       
        if (array[leftIdx] > array[rightIdx]) {
            // swap
            int temp = array[leftIdx];
            array[leftIdx] = array[rightIdx];
            array[rightIdx] = temp;

            leftIdx++;
            rightIdx--;
        }
    }
    
    array[left] = array[rightIdx];
    array[rightIdx] = pivot;   
 
    return rightIdx;
}

void quicksort (int left, int right) {
    printf ("Quicksort called with %d %d\n", left, right); 
    if (left == right || left > right) {
        return;
    }
    int pivot = partition (left, right);
    //printf ("Pivot position is %d\n", pivot);
    quicksort (left, pivot - 1);
    //printf ("First QS back\n");
    quicksort (pivot + 1, right);
    //printf ("Second QS back\n");
    return;
}

int main (void) {
    int count = 0;
    scanf ("%d", &count);

    int i = 0;
    while (i < count) {
        scanf ("%d", &array[i]);
        i++;
    }

    quicksort (0, count - 1);
    
    printf ("\n");
    i = 0;
    while (i < count) {
        printf ("%d\n", array[i]);
        i++;
    }
    printf ("\n");

    return EXIT_SUCCESS;
}

