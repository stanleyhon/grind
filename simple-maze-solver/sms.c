#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define RIGHT_PATH 0 
#define WRONG_PATH 1

struct position {
    int row;
    int col;
};

// wipes the board clean of any breadcrumbs
void cleanBreadcrumbs (char ** board) {
    int i, j;
    i = 0;
    while (i < 50) {
        j = 0;
        while (j < 50) {
            if (board[i][j] == 'b') {
                board[i][j] = ' ';
            }
            j++;
        }
        i++;
    }
    return;
}

// recursively searches till it finds the endpoint
// SO MUCH COPY PASTE FORGIVE ME.
int search (int row, int col, char ** board) { 
    // Can we go UP?
    if (row < 49 && board[row + 1][col] != '#') {
        // Yep, are we done?
        if (board[row + 1][col] == 'f') {
            // Yep, done. mark ourselves off and return
            board[row][col] = '.';
            return RIGHT_PATH;
        } else if (board[row + 1][col] == 'b') {
            // Nope, it's backtracking, don't go that way.
            // try other stuff
        } else if (board[row + 1][col] == ' ') {
            // Not sure... guess we'll check it out
            // leave a breadcrumb here so we don't go back this way
            board[row][col] = 'b';

            int result = search (row + 1, col, board);

            if (result == RIGHT_PATH) {
                // yep we get there eventually. mark ourselves off
                board[row][col] = '.';
                return RIGHT_PATH;
            } else {
                // nope this doesn't work out.
                // try other stuff.
            }
        }
    }
    
    // Can we go DOWN?
    if (row > 0 && board[row - 1][col] != '#') {
        // Yep, are we done?
        if (board[row - 1][col] == 'f') {
            // Yep, done. mark ourselves off and return
            board[row][col] = '.';
            return RIGHT_PATH;
        } else if (board[row - 1][col] == 'b') {
            // Nope, it's backtracking, don't go that way.
            // try other stuff
        } else if (board[row - 1][col] == ' ') {
            // Not sure... guess we'll check it out
            // leave a breadcrumb here so we don't go back this way
            board[row][col] = 'b';

            int result = search (row - 1, col, board);

            if (result == RIGHT_PATH) {
                // yep we get there eventually. mark ourselves off
                board[row][col] = '.';
                return RIGHT_PATH;
            } else {
                // nope this doesn't work out.
                // try other stuff.
            }
        }
    }
    
    // Can we go LEFT?
    if (col > 0 && board[row][col - 1] != '#') {
        // Yep, are we done?
        if (board[row][col - 1] == 'f') {
            // Yep, done. mark ourselves off and return
            board[row][col] = '.';
            return RIGHT_PATH;
        } else if (board[row][col - 1] == 'b') {
            // Nope, it's backtracking, don't go that way.
            // try other stuff
        } else if (board[row][col - 1] == ' ') {
            // Not sure... guess we'll check it out
            // leave a breadcrumb here so we don't go back this way
            board[row][col] = 'b';

            int result = search (row, col - 1, board);

            if (result == RIGHT_PATH) {
                // yep we get there eventually. mark ourselves off
                board[row][col] = '.';
                return RIGHT_PATH;
            } else {
                // nope this doesn't work out.
                // try other stuff.
            }
        }
    }
    
    // Can we go RIGHT?
    if (col < 49 && board[row][col + 1] != '#') {
        // Yep, are we done?
        if (board[row][col + 1] == 'f') {
            // Yep, done. mark ourselves off and return
            board[row][col] = '.';
            return RIGHT_PATH;
        } else if (board[row][col + 1] == 'b') {
            // Nope, it's backtracking, don't go that way.
            // try other stuff
        } else if (board[row][col + 1] == ' ') {
            // Not sure... guess we'll check it out
            // leave a breadcrumb here so we don't go back this way
            board[row][col] = 'b';

            int result = search (row, col + 1, board);

            if (result == RIGHT_PATH) {
                // yep we get there eventually. mark ourselves off
                board[row][col] = '.';
                return RIGHT_PATH;
            } else {
                // nope this doesn't work out.
                // try other stuff.
            }
        }
    }

    // Going any way from here does not go the right way,
    // Mark us as breadcrumbed
    board[row][col] = 'b';
    
    return WRONG_PATH;
}

// given a character, finds it's place.
// used to find the starting point
struct position findChar (char ** board, char s) {
    int i = 0;
    while (i < 50) {
        int j = 0;
        while (j < 50) {
            if (board[i][j] == s) {
                struct position p ;
                p.row = i;
                p.col = j;
                return p;
            }
            j++;
        }
        i++;
    }

    assert (0);
}

void printBoard (char ** board) {
    int i = 0;
    while (i < 50) {
        printf ("%s", board[i]);
        i++;
    }
    return;
}

int main (int argc, char * argv[]) {

    // file IO shit
    char ** board;
    board = malloc (sizeof (char*) * 50);
    int i = 0;
    while (i < 50) {
        board[i] = malloc (sizeof (char) * 50);
        memset (board[i], 0, 50);
        i++;
    }

    FILE *fp;
    char line[50];
    fp = fopen (argv[1], "r");

    assert (fp != NULL);

    i = 0;
    while (fgets (line, 50, fp) != NULL) {
        strcpy (board[i], line);
        i++;
        memset(line, 0, 50);
    }

    // print the board
    printBoard (board);

    // find the starting place
    struct position start = findChar (board, 's');

    // find the path
    search (start.row, start.col, board); 

    // clean the breadcrumbs
    cleanBreadcrumbs (board);

    // print the board with dots now
    printBoard (board);

    return EXIT_SUCCESS;
}



