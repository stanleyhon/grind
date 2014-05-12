#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1100
#define DOWN 1
#define RIGHT 2

#define MEMO_ON 1
//#define MEMO_OFF 1
int memo[SIZE][SIZE] = {0};
int dir[SIZE][SIZE] = {0};

int DP (int arr[SIZE][SIZE], int x, int y);

void printdir (int arr[SIZE][SIZE]) {
    int i, j;
    i = 0;
    while (i < SIZE) {
        j = 0;
        while (j < SIZE) {
                int r = arr[i][j];
                if (r == RIGHT) printf (" -> ");
                else printf ("  v ");
            j++;
        }
        putchar ('\n');
        i++;
    }
    return;
}

void printarr (int arr[SIZE][SIZE]) {
    int i, j;
    i = 0;
    while (i < SIZE) {
        j = 0;
        while (j < SIZE) {
            printf ("%02d ", arr[i][j]);
            j++;
        }
        putchar ('\n');
        i++;
    }
    return;
}

int main (void) {
    int arr[SIZE][SIZE];
    
    srand (time(NULL));

    int i, j;
    i = 0;
    while (i < SIZE) {
        j = 0;
        while (j < SIZE) {
            arr[i][j] = rand() % 25;
            j++;
        }
        i++;
    }

    printarr (arr);

    // Start DP magic?
    // i have no idea what i'm doing but it works
    printf ("Maximal sum is %d\n", DP (arr, 0, SIZE-1));

    printdir (dir);

    return EXIT_SUCCESS;
}

// top left is Y=SIZE, X=0
int DP (int arr[SIZE][SIZE], int x, int y) {
    int maxRight = 0;
    if (x + 1 != SIZE) {
#ifdef MEMO_ON
        // check memo first
        if (memo[x+1][y] != 0) {
            maxRight = memo[x+1][y];
        } else {
#endif
            maxRight = DP (arr, x + 1, y);
#ifdef MEMO_ON
            memo[x+1][y] = maxRight;
        }
#endif
    } 

    int maxBelow = 0;
    if (y - 1 >= 0) {
#ifdef MEMO_ON
        if (memo[x][y-1] != 0) {
            maxBelow = memo[x][y-1];
        } else {
#endif
            maxBelow = DP (arr, x, y - 1);
#ifdef MEMO_ON
            memo[x][y-1] = maxBelow;
        }
#endif
    }

    if (maxRight >= maxBelow) {
        dir[x][y] = RIGHT;
        return maxRight + arr[x][y];
    } else {
        dir[x][y] = DOWN;
        return maxBelow + arr[x][y];
    }

    return -1;
}
