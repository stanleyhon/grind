#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ARRAY_SIZE 100

void bubbleSort (int * array, int maxIdx) {
    if (maxIdx == 0) return;

    int leftIdx = 0;

    int clean = 0;
    while (clean == 0) {
        clean = 1;
        leftIdx = 0;
        while (leftIdx <= maxIdx - 1) {
            if (array[leftIdx] > array[leftIdx + 1]) {
                int temp = array[leftIdx];
                array[leftIdx] = array[leftIdx + 1];
                array[leftIdx + 1] = temp;

                clean = 0; // we had to work, not clean
            }
            leftIdx++;
        }
    }
    return;
}

void printArray (int * array, int maxIdx) {
    int idx = 0;
    while (idx <= maxIdx) {
       printf ("%d\n", array[idx]);
       idx++;
    }
    return;
}

int main (int argc, char * argv[]) {
    FILE * fp;
    fp = fopen (argv[1], "r");
    assert (fp != NULL);

    int * array = malloc (sizeof (int) * ARRAY_SIZE);

    int index = 0;
    while (fscanf (fp, "%d", &array[index]) != EOF) {
        index++;
    }

    // print
    printArray (array, index - 1);
    printf ("******************\n");
    // sort
    bubbleSort (array, index - 1);
    // print
    printArray (array, index - 1);
    
    return EXIT_SUCCESS;
}
