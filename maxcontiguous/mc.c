#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 25
#define EXTEND 1
#define NEW 0
int array[SIZE];

void dp (int * start, int * finish);
int main (void) {

    srand (time (NULL));

    int idx = 0;
    while (idx < SIZE) {
        array[idx] = rand () % 1000;

        int negative = rand () % 10;
        if (negative < 2) {
            array[idx] = array[idx] * -1;
        }
        idx++;
    }

    int start, finish;

    dp (&start, &finish);
    
    idx = 0;
    while (idx < SIZE) {
        if (start == idx) {
            printf ("[S]");
        } else if (finish == idx) {
            printf ("[F]");
        }
        printf ("%d ", array[idx]);
        idx++;
    }
    printf ("\n");


}

void dp (int * startRet, int * finishRet) {
    int runningMax = array[0];
    int currentMax = array[0];

    int start = 0;
    int temp_start = 0;
    int end = 0;

    int idx = 0;
    while (idx < SIZE) {
        if (currentMax < 0) {
            currentMax = array[idx];
            temp_start = idx;
        } else {
            currentMax += array[idx];
        }

        if (currentMax >= runningMax) {
            runningMax = currentMax;
            start = temp_start;
            end = idx;
        }
        idx++;
    }

    *startRet = start;
    *finishRet = end;
}

