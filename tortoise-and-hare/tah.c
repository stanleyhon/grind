#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node * next;
};

typedef struct node * Node;

Node create (Node next) {
    Node n = malloc (sizeof (struct node));
    n->next = next;
    return n;
}

#define CYCLE 1
#define NO_CYCLE 0

int tah (Node head) {
    Node tortoise = head;
    Node hare = head;
    while (tortoise != NULL && hare != NULL) {
        tortoise = tortoise->next;
        hare = hare->next;
        if (hare != NULL) {
            hare = hare->next;
        }
        if (tortoise == hare) { // they point to the same thing
            return CYCLE;
        }
    }
    return NO_CYCLE;
}


int main (void) {
    Node n = create (NULL);
    n->next = create (NULL);
    n->next->next = create (NULL);
    n->next->next->next = create (NULL);
    n->next->next->next->next = create (NULL);
    n->next->next->next->next ->next = create (NULL);
    n->next->next->next->next ->next ->next = create (NULL);
    n->next->next->next->next ->next ->next ->next = create (NULL);
    n->next->next->next->next ->next ->next ->next ->next = create (NULL);
    n->next->next->next->next ->next ->next ->next ->next ->next = create (NULL);
    // make it loop by setting the end back to the something
    // n->next->next->next->next = n->next;

    printf ("%s", tah (n) ? "There is a cycle\n" : "There is no cycle\n");

    return EXIT_SUCCESS;
}


