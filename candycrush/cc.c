#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SIZE 1000
#define COLOURS 2

#define NONE -1
#define UP 0
#define DOWN 1
#define LEFT 3
#define RIGHT 4

#define CLEAN 0 
#define DIRTY 1

void printBoard (int array[SIZE][SIZE]);
void generateRandom (int array[SIZE][SIZE]);
int removeTriples (int array[SIZE][SIZE]);
void fixTriple (int array[SIZE][SIZE], int direction, int row, int col);
int checkNeighbours (int array[SIZE][SIZE], int row, int col);

int array[SIZE][SIZE];

int main ( void ) {

    srand(time(NULL));

    // generate random board.
    generateRandom (array);
    // printBoard (array);

    // stop three in a row?
    int result = DIRTY;
    int count = 0;
    while (result == DIRTY) {
        result = removeTriples (array); 
        count++;
//        printBoard (array);
    }

    printf ("Finished in %d iterations\n", count);

    fflush(stdout);
    return EXIT_SUCCESS;
}

void generateRandom (int array[SIZE][SIZE]) {
    int row = 0;
    int col;
    while (row < SIZE) {
        col = 0;
        while (col < SIZE) {
            array[row][col] = rand() % COLOURS;
            col++;
        }
        row++;
    }
    return;
}

void printBoard (int array[SIZE][SIZE]) {
    int row, col;
    row = 0;
    while (row < SIZE) {
        col = 0;
        while (col < SIZE) {
            printf ("%d", array[row][col]);
            col++;
        }
        printf ("\n");
        row++;
    }

    printf ("\n\n");
    return;
}

int removeTriples (int array[SIZE][SIZE]) {
    int cleanBoard = CLEAN;
    int row, col;
    row = 0;
    while (row < SIZE) {
        col = 0;
        while (col < SIZE) {
            // check neighbours.
            int direction = checkNeighbours (array, row, col);
            if (direction != NONE) {
                cleanBoard = DIRTY;
                
                // if neighbours form triple
                // fix neighbours 
                fixTriple (array, direction, row, col);
            }
            col++;
        }
        row++;
    }
    return cleanBoard;
}

void fixTriple (int array[SIZE][SIZE], int direction, int row, int col) {
    int rowScale = 0;
    int colScale = 0;

    if (direction == UP) {
        rowScale = 1;
    } else if (direction == DOWN) {
        rowScale = -1;
    } else if (direction == LEFT) {
        colScale = -1;
    } else if (direction == RIGHT) {
        colScale = 1;
    }

    // reroll all of it
    array[row][col] = rand() % COLOURS;
    array[row+rowScale][col+colScale] = rand() % COLOURS;
    array[row+rowScale*2][col+colScale*2] = rand() % COLOURS;

    return;
}

int checkNeighbours (int array[SIZE][SIZE], int row, int col) {
    int canGoUp = 0;
    int canGoDown = 0;
    int canGoLeft = 0;
    int canGoRight = 0;

    if (row + 2 < SIZE) {
        canGoUp = 1;
     }
    if (row - 2 >= 0) {
        canGoDown = 1;
    }
    if (col + 2 < SIZE) {
        canGoRight = 1;
    }
    if (col - 2 >= 0) {
        canGoLeft = 1;
    }

    int search = array[row][col];

    if (canGoUp) {
        if (search == array[row+1][col] && search == array[row+2][col]) {
            return UP;
        }
    }
    if (canGoDown) {
        if (search == array[row-1][col] && search == array[row-2][col]) {
            return DOWN;
        }
    }
    if (canGoLeft) {
        if (search == array[row][col-1] && search == array[row][col-2]) {
            return LEFT;
        }
    }
    if (canGoRight) {
        if (search == array[row][col+1] && search == array[row][col+2]) {
            return RIGHT;
        }
    }

    return NONE;
}
