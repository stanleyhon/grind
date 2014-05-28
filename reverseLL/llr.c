// I actually wrote this shit in google docs for practice
// unsurprisingly there were bugs.

struct node {
    int payload;
    struct node * next;
};

struct linkedList {
    int length;
    struct node * first;
};

#include <stdio.h>
#include <stdlib.h>

void insert (struct linkedList * list, int payload);
void reverse (struct linkedList * list);
void printList (struct linkedList * list);

int main (void) {
    struct linkedList * aList = malloc (sizeof (struct linkedList));
    aList->length = 0;
    aList->first = NULL;
    
    insert (aList, 1);
    insert (aList, 2);
    insert (aList, 3);
    insert (aList, 4);
    insert (aList, 5);
    insert (aList, 6);
    insert (aList, 7);
    insert (aList, 8);
    insert (aList, 9);
    insert (aList, 10);
    insert (aList, 11);
    insert (aList, 12);
    insert (aList, 13);

    printList (aList);

    reverse (aList);
    
    printList (aList);

    return EXIT_SUCCESS;
}

void insert (struct linkedList * list, int payload) {
    struct node * current;
    current = list->first;

struct node * newNode = malloc (sizeof (struct node));
    newNode->payload = payload;
    newNode->next = NULL;

    if (current == NULL) {  
        // hook it up to the LL struct
        list->first = newNode;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
    current->next = newNode;
    }
    list->length++;
    return;
}

void reverse (struct linkedList * list) {
    if (list->first != NULL && list->first->next != NULL) {

        // first run, remember the first node
        struct node * current = list->first;

        // remember the one after that
        struct node * rememberNext = current->next;

        // flag for first run
        int firstNode = 1;

        while (rememberNext != NULL) {
            // remember the one after the right hand
            struct node * third = rememberNext->next;
            
            // make the right hand, point to the left hand
            rememberNext->next = current;

            // if first run set current->next to null
            if (firstNode) {
                current->next = NULL;
                firstNode = 0;
            }

            // and next time,
            current = rememberNext;

            // keep changing the head of the list as we go
            list->first = rememberNext;

            rememberNext = third;
        }
    }
    return;
}

void printList (struct linkedList * list) {
    struct node * current = list->first;
    while (current != NULL) {
        printf ("[%d]->", current->payload);
        current = current->next;
    }
    printf ("NULL\n");
    return;
}

