// Given a linked list that has one quirk - every node has an /extra/ pointer to some random node
// in the linked list.

// Write an in-place, O(n) function that can deep copy the linked list

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    struct Node * next;
    struct Node * enemy;
    int uniqueID;
};

void printList (struct Node * head) {
    while (head != NULL) {
        printf ("%d[%d] ->", head->uniqueID, head->enemy->uniqueID);
        head = head->next;
    }

    printf (" X\n");
    return;
}

struct Node * newNode () {
    struct Node * new = malloc (sizeof (struct Node));
    new->enemy = NULL;
    new->next = NULL;
    new->uniqueID = rand () % 100;
    return new;
}

struct Node * newNodeWithInfo (struct Node * next, struct Node * enemy, int uniqueID) {
    struct Node * new = newNode ();
    new->enemy = enemy;
    new->next = next;
    new->uniqueID = uniqueID;
    return new;
}

void delete (struct Node * head) {
    while (head != NULL) {
        struct Node * del = head;
        head = head->next;
        del->next = NULL;
        del->enemy = NULL;
        del->uniqueID = -1;
        free (del);
    }
    return;
}


struct Node * deepCopy (struct Node * head) {
    struct Node * originalHead = head;
    // copy the list but put the nodes between the old list
    while (head != NULL) {
        struct Node * new = newNodeWithInfo (head->next, NULL, head->uniqueID);
        new->next = head->next;
        head->next = new;
        head = new->next;
    }
    
    // setup the enemies
    struct Node * ptr = originalHead;
    while (ptr != NULL) {
        ptr->next->enemy = ptr->enemy->next;
        ptr = ptr->next->next;
    }

    // split the list
    struct Node * returnPtr = originalHead->next;

    ptr = originalHead;
    struct Node * newList = ptr->next;
    while (ptr != NULL) {
        ptr->next = newList->next;
        if (newList->next != NULL) {
            newList->next = newList->next->next;
        }
        newList = newList->next;
        ptr = ptr->next;
    }

    return returnPtr;
}

int main (void) {
    srand (time (NULL));
    struct Node * newList = newNode ();
    newList->next = newNode ();
    newList->next->next = newNode ();
    newList->next->next->next = newNode ();

    newList->enemy = newList->next->next;
    newList->next->enemy = newList;
    newList->next->next->enemy = newList;
    newList->next->next->next->enemy = newList->next->next;

    printf ("Old list: ");
    printList (newList); 

    struct Node * clone = deepCopy (newList);

    printf ("clone list: ");
    printList (clone);

    delete (newList);

    printf ("clone list: ");
    printList (clone);
    

    return EXIT_SUCCESS;
}


