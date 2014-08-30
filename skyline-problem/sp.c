// The 'skyline' problem

// inputs are many (rangeLow, height, rangeHigh) triplets indicating
// a building starting from rangeLow -> rangeHigh of that height.

// Output looks like (x, newHeight) pairs indicating a change of height
// at point X, to the new height

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int rangeLow;
    int rangeHigh;
    int height;
    struct node * left;
    struct node * right;
};

struct node * newNode (int rl, int rh, int h) {
    struct node * new = malloc (sizeof (struct node));
    new->rangeLow = rl;
    new->rangeHigh = rh;
    new->height = h;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void insert (int rl, int rh, int h, struct node * tree) {
    // is the interval completely separate?
    if (rh <= tree->rangeLow && rh <= tree->rangeHigh) { // left
        if (tree->left == NULL) { // just put it here
            tree->left = newNode (rl, rh, h);
        } else {
            insert (rl, rh, h, tree->left);
        }

    } else if (rl >= tree->rangeLow && rl >= tree->rangeHigh) { // right
        if (tree->right == NULL) { // just put it here
            tree->right = newNode (rl, rh, h);
        } else {
            insert (rl, rh, h, tree->right);
        }

    } else { // need to split interval.
        assert (rl <= tree->rangeHigh || rh >= tree->rangeLow);

        // figure out the left interval
        if (rl < tree->rangeLow) { // there is some
            // call insert with the lower interval
            insert (rl, tree->rangeLow, h, tree);
        }

        // figure out the right interval
        if (rh > tree->rangeHigh) { // there is some
            // call insert with the upper interval
            insert (tree->rangeHigh, rh, h, tree);
        }
    }
}

struct node * lastNode = NULL;

void printResultVector (struct node * tree) {
    // traverse the tree in... left root right
    if (tree->left != NULL) {
        printResultVector (tree->left);
    }

    // print ourselves
    printf ("[%d h-%d]\n", tree->rangeLow, tree->height);

    if (tree->right != NULL) {
        printResultVector (tree->right);
    }

    if (tree->right == NULL) {
        lastNode = tree;
    }

    return;
}

int main (void) {
    struct node * tree = NULL;
    int rl, rh, h;
    while (scanf ("%d %d %d", &rl, &h, &rh) == 3) {
        printf ("Inserting %d %d %d\n", rl, h, rh);
        if (tree == NULL) {
            tree = newNode (rl, rh, h);
        } else {
            insert (rl, rh, h, tree);
        }
    }

    printResultVector (tree);

    printf ("[%d h-%d]\n", lastNode->rangeHigh, 0);

    return EXIT_SUCCESS;
}
