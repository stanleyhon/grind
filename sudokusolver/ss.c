#include <stdio.h>
#include <stdlib.h>

#define INVALID 0
#define VALID 1

#define UNSOLVED 0
#define SOLVED 1
int board[9][9];
int pSol[9][9][10]; // 3D array, basically list for each element of things we think
// it could be. Index 9 holds how many solutions we have for this tile.

int solve (void);
void reduce (int currentRow, int currentCol);
void generate (int currentRow, int currentCol);
int checkValid (int currentRow, int currentCol, int value);
int checkSquare (int currentRow, int currentCol, int value);
int checkVert (int currentCol, int value);
int checkHor (int currentRow, int value);
void printBoard (void);

int main (void) {
    int currentRow = 0;
    while (currentRow < 9) {
        int currentCol = 0;
        while (currentCol < 9) {
            char * string = malloc (sizeof (char));
            scanf ("%s", string);

            if (*string == 'X') {
                board[currentRow][currentCol] = -1;
            } else {
                board[currentRow][currentCol] = atoi (string);
            }
            currentCol++;
        }
        currentRow++;
    }
    while (solve () == UNSOLVED) {
        solve();
    }

    // TODO:
    // now its possible there are no sure solutions, check for this case
            
    return EXIT_SUCCESS;
}


int solve (void) {
    int gotIn = 0;
    int currentRow = 0;
    while (currentRow < 9) {
        int currentCol = 0;
        while (currentCol < 9) {
            if (board[currentRow][currentCol] == -1) { // we need to fill this in
                gotIn = 1;
                if (pSol[currentRow][currentCol][9] == 1) { // find that solution and just chuck it in
                    int idx = 0;
                    while (idx < 9) {
                        if (pSol[currentRow][currentCol][idx] != 0) {
                            board[currentRow][currentCol] = pSol[currentRow][currentCol][idx];
                            pSol[currentRow][currentCol][idx] = 0;
                            pSol[currentRow][currentCol][9] = 0;
                            break;
                        }
                        idx++;
                    }
                    currentCol++;
                    continue;
                }

                // do we have solutions we think it could be already?
                if (pSol[currentRow][currentCol][9] == 0) { // no, generate.
                    generate (currentRow, currentCol);
                } else { // yes, reduce
                    reduce (currentRow, currentCol);
                }
            }
            currentCol++;
        }
        currentRow++;
    }
    printBoard ();
    printf ("\n\n");
    if (gotIn == 1) {
        return UNSOLVED;
    } else {
        return SOLVED;
    }
}

void generate (int currentRow, int currentCol) {
    // generation involves looping over 1-9, checking validity and adding to the valid list
    // if it turns out there's only 1 valid, write it in
    int candidate = 1;
    while (candidate <= 9) {
        if (checkValid (currentRow, currentCol, candidate) == VALID) {
            int i = 0;
            while (i < 9) {
                if (pSol[currentRow][currentCol][i] == 0) {
                    pSol[currentRow][currentCol][i] = candidate;
                    pSol[currentRow][currentCol][9]++;
                    break;
                }
                i++;
            }
        }
        candidate++;
    }
    printf ("There are possibly %d solutions for %d %d\n", pSol[currentRow][currentCol][9], currentRow, currentCol);
    return;
}

void reduce (int currentRow, int currentCol) {
    int idx = 0;
    while (idx < 9) {
        if (pSol[currentRow][currentCol][idx] != 0) { // lets check again see if it's valid

            // check to see if its valid
            if (checkValid (currentRow, currentCol, pSol[currentRow][currentCol][idx]) == INVALID) {
                // remove it
                pSol[currentRow][currentCol][idx] = 0;
                pSol[currentRow][currentCol][9]--;
            }

            // now see if we've narrowed it down to just one
            if (pSol[currentRow][currentCol][9] == 1) { // yes, find it and put it in
                int i = 0;
                while (i < 9) {
                    if (pSol[currentRow][currentCol][i] != 0) {
                        board[currentRow][currentCol] = pSol[currentRow][currentCol][i];
                        pSol[currentRow][currentCol][i] = 0;
                        pSol[currentRow][currentCol][9] = 0;
                        break;
                    }
                    i++;
                }
            } // otherwise just continue
        }
        idx++;
    }
    return;
}


int checkValid (int currentRow, int currentCol, int value) {
    if (checkSquare (currentRow, currentCol, value) &&
        checkVert (currentCol, value) &&
        checkHor (currentRow, value)) {
        return VALID;
    } else {
        return INVALID;
    }
}

int checkSquare (int currentRow, int currentCol, int value) {
    // first do square check see if there's a dupe in the square already
    int rootRow = (currentRow / 3) * 3;
    int rootCol = (currentCol / 3) * 3;
    // now walk the square checking for our value
    int rowInc = 0;
    while (rowInc < 3) {
        int colInc = 0;
        while (colInc < 3) {
            if (board[rootRow + rowInc][rootCol + colInc] == value) { // ok this is clearly not a solution
                return INVALID;
            }
            colInc++;
        }
        rowInc++;
    }
    return VALID;
}

int checkHor (int currentRow, int value) {
    // check to see if there is this value in that row
    int idx = 0;
    while (idx < 9) {
        if (board[currentRow][idx] == value) {
            return INVALID;
        }
        idx++;
    }
    return VALID;
}

int checkVert (int currentCol, int value) {
    // check to see if the value is in this column
    int idx = 0;
    while (idx < 9) {
        if (board[idx][currentCol] == value) {
            return INVALID;
        }
        idx++;
    }
    return VALID;
}

void printBoard (void) {
    int currentRow = 0;
    while (currentRow < 9) {
        int currentCol = 0;
        while (currentCol < 9) {
            if (board[currentRow][currentCol] == -1) {
                printf ("X ");
            } else {
                printf ("%d ", board[currentRow][currentCol]);
            }
            currentCol++;
        }
        printf ("\n");
        currentRow++;
    }
    return;
}


































