#include <stdio.h>
#include <stdlib.h>



struct node {
    struct node * left;
    struct ndoe * right;
    int payload;
};

void printTree (struct node * tree, int payload) {
    printf ("%d\n", tree->payload);
    if (tree->left != NULL) printTree (tree->left);
    if (tree->right != NULL) printTree (tree->right);

void insert (struct node * tree, int payload) {
    if (payload >= tree->payload) {
        if (tree->right == NULL) {
            struct node * newNode = malloc (sizeof (struct node));
            newNode->payload = payload;
            tree->right = newNode;
            return;
        } else {
            insert (tree->right, payload);
        }
    } else {
        if (tree->left == NULL) {
            struct node * newNode = malloc (sizeof (struct node));
            newNode->payload = payload;
            tree->left = newNode;
            return;
        } else {
            insert (tree->left, payload);
        }
    }
    return;
}

int main (void) {
    struct node * newTree = malloc (sizeof (struct node));
    insert (newtree, 10);
    insert (newTree, 5);
    insert (newTree, 15);
    insert (newTree, 7);
    insert (newTree, 3);
    insert (newTree, 12);
    insert (newTree, 18);



