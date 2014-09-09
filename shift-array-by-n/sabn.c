#include <stdio.h>
#include <stdlib.h>

void reverse (int * array, int start, int end) {
    while (start < end) {
        int temp = array[start];
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    }
    return;
}

#define LEFT 0
#define RIGHT 1
void shiftn (int * array, int length, int shift, int direction) {
    shift = shift % length;
    // 1. reverse the list
    reverse (array, 0, length - 1);

    // 2. if right, reverse first <shift> elements then reverse the rest
    if (direction == RIGHT) {
        reverse (array, 0, shift-1);
        reverse (array, shift, length-1);
    // 2. if left, reverse first <length - shift> elements, then reverse the rest
    } else if (direction == LEFT) {
        reverse (array, 0, (length - 1 - shift));
        reverse (array, (length - shift), length - 1);
    }
    return;
}

int main (void) {
    int * array = malloc (sizeof (int) * 8);
    int idx = 0;
    while (idx < 8) {
        array[idx] = idx + 1;
        idx++;
    } 

    idx = 0;
    while (idx < 8) {
        printf ("%d ", array[idx]);
        idx++;
    }
    printf ("\n");

    shiftn (array, 8, 2, LEFT);

    idx = 0;
    while (idx < 8) {
        printf ("%d ", array[idx]);
        idx++;
    }
    printf ("\n");

    return EXIT_SUCCESS;
}


