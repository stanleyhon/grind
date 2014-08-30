#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node * left;
    struct node * right;
};

struct node * new_node (int value) {
    struct node * newNode = malloc (sizeof (struct node));
    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

void insert_new (int value, struct node * head) {
    struct node * target = head;
    if (target->value <= value) {
        if (target->right != NULL) {
            insert_new (value, target->right);
        } else { // not null, put it here
            target->right = new_node (value);
            return;
        }
    } else { // value is less, go left
        if (target->left != NULL) {
            insert_new (value, target->left);
        } else {
            target->left = new_node (value);
            return;
        }
    }
}

void print_tree (struct node * tree) {
    if (tree == NULL) return;
    printf ("%d ", tree->value);
    printf ("LEFT: ");
    print_tree (tree->left);
    printf ("RIGHT: ");
    print_tree (tree->right);
    return;
}

struct node * new_heads[100];
int nextFree = 0;

int firstLoop = 1;

void reverse_tree (struct node * head) {
    if (head->left == NULL && head->right == NULL) {
        new_heads[nextFree] = head;
        nextFree++;
        return;
    }

    int firstRun = firstLoop;
    firstLoop = 0;

    if (head->left != NULL) {
        reverse_tree (head->left);
        head->left->left = NULL;
        head->left->right = head;
    }

    if (head->right != NULL) {
        reverse_tree (head->right);
        head->right->left = head;
        head->right->right = NULL;
    }

    if (firstRun == 1) {
        head->left = NULL;
        head->right = NULL;
    }

    return;
}

int main (void) {
    struct node * b_tree = new_node (15);
    insert_new (6, b_tree);
    insert_new (14, b_tree);
    insert_new (4, b_tree);
    insert_new (9, b_tree);
    insert_new (12, b_tree);
    insert_new (2, b_tree);
    insert_new (3, b_tree);
    insert_new (24, b_tree);

    print_tree (b_tree);

    reverse_tree (b_tree);

    printf ("REVERSING...\n");

    int idx = 0;
    while (idx < nextFree) {
        print_tree (new_heads[idx]);
        printf ("\n*********\n");
        idx++;
    }

    
    return EXIT_SUCCESS;
}
