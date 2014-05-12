#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 50
#define DENSITY 20
void prettyPrint (int** array);
int** makeArray ();
void populate (int** array);
void iterate (int** source, int** new);
int countNeighbours (int x, int y, int** array);

int main (void) {
    int** layer1 = makeArray();
    int** layer2 = makeArray();
    int** temp;
    srand(time(NULL));

    populate (layer1);

    prettyPrint (layer1);

    while (1) {
        getchar();
        iterate (layer1, layer2);

        prettyPrint (layer2);

        temp = layer1;
        layer1 = layer2;
        layer2 = temp;
        
    }
    return 0;
}

int** makeArray () {
    int** retArray = malloc(sizeof(int**)*SIZE);
    int i = 0;
    while (i < SIZE) {
        retArray[i] = malloc(SIZE*sizeof(int));
        i++;
    }

    return retArray;
}


void populate (int** array) {
    int i, j;
    i = 0;
    while (i < SIZE) {
        j = 0;
        while (j < SIZE) {
            if (rand() % DENSITY == 0) {
                array[i][j] = 1;
            } else {
                array[i][j] = 0;
            }
            j++;
        }
        i++;
    }
    return;
}

void iterate (int** source, int** new) {
    int i, j;
    i = 0;
    while (i < SIZE) {
        j = 0;
        while (j < SIZE) {
            int neighbours = countNeighbours (i, j, source);
            if (source[i][j] == 1) {
                // fewer than 2 neighbours - dies
                if (neighbours < 2) new[i][j] = 0;
                // 2-3 neighbours - lives
                if (neighbours == 2 || neighbours == 3) new[i][j] = 1;
                // 4+ neighbours - dies
                if (neighbours >= 4) new[i][j] = 0;
            } else {
                // if 3 - live
                if (neighbours == 3) new[i][j] = 1;
                else new[i][j] = 0;
            }
            j++;   
        }
        i++;
    }
    return;
}

int countNeighbours (int x, int y, int** array) {
    int count = 0;
    int canGoLeft = 0;
    int canGoRight = 0;
    int canGoDown = 0;
    int canGoUp = 0;

    if (x-1 >= 0) {
        canGoLeft = 1;
    }
    if (x+1 < SIZE) {
        canGoRight = 1;
    }
    if (y+1 < SIZE) {
        canGoUp = 1;
    }
    if (y-1 >= 0) {
        canGoDown = 1;
    }

    if (canGoLeft) {
        if (array[x-1][y]) count++;
        if (canGoUp) {
            if (array[x-1][y+1]) count++;
        }
        if (canGoDown) {
            if (array[x-1][y-1]) count++;
        }
    }

    if (canGoUp) {
        if (array[x][y+1]) count++;
    }

    if (canGoDown) {
        if (array[x][y-1]) count++;
    }

    if (canGoRight) {
        if (array[x+1][y]) count++;
        if (canGoUp) {
            if (array[x+1][y+1]) count++;
        }
        if (canGoDown) {
            if (array[x+1][y-1]) count++;
        }
    }

    return count;
}

void prettyPrint (int** array) {
    int x = 0;
    int y = SIZE-1;
    while (y >= 0) {
        x = 0;
        while (x < SIZE-1) {
            if (array[x][y] == 1) {
                printf ("#");
            } else {
                printf (" ");
            }
            x++;
        }
        printf ("\n");
        y--;
    }
    printf ("********************************************************\n");
    return;
}

