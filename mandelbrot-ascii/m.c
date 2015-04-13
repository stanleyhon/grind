#include <stdio.h>
#include <stdlib.h>

#define ITERATION_THRESHOLD 1000 
// so i think it was... Z^2 + 1? and you recursively apply
// A^2 + 1, where A was the result of Z^2 + 1 a lot of times
// until it either escapes or ossilicates.

void myrecurse (double inputReal, double inputIma, double * escapeReal, double * escapeIma);

int escapeSteps (double x, double y) {
    double real = 0;
    double ima = 0;
    int iteration = 0;
    while (((real*real) + (ima*ima) < 4) && iteration < ITERATION_THRESHOLD) {
        double xtemp = real*real - ima*ima + x;
        ima = 2*real*ima + y;
        real = xtemp;
        iteration++;
    }
    
    if (iteration >= ITERATION_THRESHOLD && ((real*real) + (ima*ima) < 4)) {
        // didn't escape.
        return 0;
    } else {
        // escaped after iteration recursions.
        return iteration;
    }    
}
 
#define CENTER_OFFSET_X -1
#define CENTER_OFFSET_Y 100 

// 
// distance is going to be 2^-zoom
void render (int size, int zoom) {
    double distance = 2;
    int power = 0;
    while (power < zoom) {
        distance = distance * 2;
        power++;
    }
    distance = 1 / distance;

    printf ("Distance is %f\n", distance);
    // render top left to bottom right.
    double currentY = (distance * size / 2) + CENTER_OFFSET_Y;
    while (currentY > ((-1) * (distance * size / 2))) {
        double currentX = (-1) * (distance * size / 2) + CENTER_OFFSET_X;
        while (currentX < (distance * size / 2)) {
            if (escapeSteps(currentX, currentY) != 0) {
                printf (" ");
            } else {
                printf ("*");
            }
            currentX += distance;
        }
        printf ("\n");
        currentY -= distance;
    }
}

int main (void) {
    render (100, 5);
    return 0;
}
