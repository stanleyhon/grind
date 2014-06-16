#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int pascal (int row, int col) {

    assert (row >= 0 && col >= 0);
    if (row == 0 && col == 0) {
        return 1;
    } else {
        // we're not the left edge, get the left value
        int leftValue = 0;
        int rightValue = 0;
        if (col != 0) {
            leftValue = pascal (row - 1, col - 1);
        } 

        // we're not the right edge, get right value
        // each row has the same number of columns
        // i.e. row 0 has 1 column
        if (col != row) {
            rightValue = pascal (row - 1, col);
        }

        return leftValue + rightValue;
    }

    assert (0);
    return -1;
}

int main (void) {

    int row, col;
    assert (scanf ("%d %d", &row, &col) == 2);

    printf ("%d\n", pascal (row, col));

    return EXIT_SUCCESS;
}




