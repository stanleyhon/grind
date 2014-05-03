#include <stdio.h>
#include <stdlib.h>

struct node {
    int payload;
    struct node * next;
};

struct linkedList {
    struct node * firstNode;
    int length;
};

int list_insert (struct linkedList * targetList, int payload) {
    // make a new node
    struct node * newNode = malloc(sizeof(struct node));
    newNode->payload = payload;
    newNode->next = NULL;

    // figure out where to put it
    struct node * currentNode = targetList->firstNode;
    if (currentNode == NULL) {
        targetList->firstNode = newNode;
    } else {
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }

        // at this point currentNode->next is NULL
        // put out new node in
        currentNode->next = newNode;
    }

    return 0;
}

int list_print (struct linkedList * targetList) {
    struct node * currentNode = targetList->firstNode;

    while (currentNode != NULL) {
        printf("%d -> ", currentNode->payload);
        currentNode = currentNode->next;
    }

    printf("NULL\n");
    return 0;
}

int list_destroy (struct linkedList * targetList) {
    struct node * currentNode = targetList->firstNode;

    free(targetList);

    while (currentNode != NULL) {
        struct node * dead = currentNode;

        currentNode = currentNode->next;

        free(currentNode);
    }

    return 0;
}


int main (void) {

    // make a new linkedList!
    struct linkedList * myList = malloc(sizeof(struct linkedList));

    // make a new node!
    myList->firstNode = malloc(sizeof(struct node));
    myList->firstNode->payload = 69;
    myList->firstNode->next = NULL;

    // make another new node!
    struct node * newNode = malloc(sizeof(struct node));
    newNode->payload = 1234;
    newNode->next = NULL;

    // attach it
    myList->firstNode->next = newNode;

    // see what's going on
    list_print(myList);

    // reverse the list!
    struct node * temp = myList->firstNode; // keep track of the original first
    myList->firstNode = myList->firstNode->next; // new first is the second node
    myList->firstNode->next = temp; // new first's next is the original
    myList->firstNode->next->next = NULL; // the original's next should be NULL

    // see what's going on
    list_print(myList);

    // use helper to add to the list!
    list_insert(myList, 99);
    list_insert(myList, 1032);
    list_insert(myList, 4);
    list_insert(myList, -4);
    list_insert(myList, 0x12351);
    list_insert(myList, 0b111010111);
    list_insert(myList, 0x412);

    // use helper to print it out
    list_print(myList);

    // destroy it!
    list_destroy(myList);

    return 0;
}
