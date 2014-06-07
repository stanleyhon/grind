#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int array[1000];

void mymergesort (int i, int j) {
    if (i == j) {
        return;
    }
   
    int partition = i + (j-i)/2;
    mymergesort (i, partition);
    mymergesort (partition + 1, j);

    // merge.

    int leftHand = i;
    int rightHand = partition + 1;

    int buffer[1000];
    memset (buffer, -1, 1000);

    int writeIndex = i;
    int leftDepleted = 0;
    int rightDepleted = 0;
    while (writeIndex <= j) {
        if ((array[leftHand] <= array[rightHand] && leftDepleted == 0) || rightDepleted == 1) {
            buffer[writeIndex] = array[leftHand];
            leftHand++;
            if (leftHand > partition) leftDepleted = 1;
        } else {
            buffer[writeIndex] = array[rightHand];
            rightHand++;
            if (rightHand > j) rightDepleted = 1;
        }
        writeIndex++;
    }

    // copy it back
    int copyIdx = i;
    while (copyIdx <= j) {
        array[copyIdx] = buffer[copyIdx];
        copyIdx++;
    }

    return;
}

int main (void) {
    int idx = 0;

    printf ("how many? ");
    int count;
    scanf ("%d", &count);

    while (idx < count) {
        scanf ("%d", &array[idx]);
        idx++;
    }

    mymergesort (0, count - 1);

    printf ("\n");
    idx = 0;
    while (idx < count) {
        printf ("%d\n", array[idx]);
        idx++;
    }


    return EXIT_SUCCESS;
}
