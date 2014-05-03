#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char counter(char previous) {
    if (previous == 'S') {
        return 'R';
    } else if (previous == 'R') {
        return 'P';
    } else {
        return 'S';
    }

    return 'Z';
}

int main (void) {
    srand (time(NULL));

    char previous = 'P';

    while (1) {

        printf("**************************************\n");

        char play = 'Z';
        printf("your move? [S, P, R]: ");
        while (play != 'S' && play != 'P' && play != 'R') {
            scanf("%c", &play);
        }

        char ourPlay;

        int val = rand() % 4;
        if (val == 0) {
            ourPlay = 'S';
        } else if (val == 1) {
            ourPlay = 'P';
        } else if (val == 2) {
            ourPlay = 'R';
        } else if (val == 3) {
            ourPlay = counter(previous);
        }

        printf("I play %c\n", ourPlay);

        previous = play;

        if (play == ourPlay) {
            printf("nobody wins\n");
            continue;
        }

        if (play == 'P') {
            if (ourPlay == 'S') {
                printf ("I win!\n");
            } else {
                printf ("You win!\n");
            }
        } else if (play == 'R') {
            if (ourPlay == 'P') {
                printf ("I win!\n");
            } else {
                printf ("You win!\n");
            }
        } else {
            if (ourPlay == 'R') {
                printf("I win!\n");
            } else {
                printf ("you win!\n");
            }
        }
    }

    return EXIT_SUCCESS;
}





