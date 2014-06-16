#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct nodeInfo {
    int id;
    int parentId;
    int weight;
    int subtreeWeight;
    struct nodeInfo * next; // linked list of these
};

int subtreeCalculate (struct nodeInfo * root, struct nodeInfo * nodeList);

int main (void) {
    // Read in graph CSV
    struct nodeInfo * list = NULL;
    struct nodeInfo * target = NULL;
    int id;
    int parentId;
    int weight;
    while (scanf ("%d,%d,%d", &id, &parentId, &weight) == 3) {
        struct nodeInfo * new = malloc (sizeof (struct nodeInfo));
        new->id = id;
        new->parentId = parentId;
        new->weight = weight;
        new->next = NULL;
        if (list == NULL) {
            list = new;
            target = list;
        } else {
            target->next = new;
            target = target->next;
        }
    }

    assert (list != NULL && target != NULL);

    // find the root node
    struct nodeInfo * root = list;
    while (root->parentId != 0 && root->next != NULL) {
        root = root->next;
    }

    assert (root->parentId == 0);

    // fill in subtreeWeight;
    subtreeCalculate (root, list);

    // print it out see if it makes sense.
    struct nodeInfo * printTarget = list;
    while (printTarget != NULL) {
        printf ("id: %d subtreeWeight: %d\n", printTarget->id, printTarget->subtreeWeight);
        printTarget = printTarget->next;
    }

    // TODO: so much leak. dw...

    return EXIT_SUCCESS;
}

int subtreeCalculate (struct nodeInfo * root, struct nodeInfo * nodeList) {
    int totalWeight = 0;
    int rootId = root->id;
    struct nodeInfo * current = nodeList;

    // recurse on all direct children.
    while (current != NULL) {
        if (current->parentId == rootId) { // This is a child
            totalWeight += subtreeCalculate (current, nodeList);
        }
        current = current->next;
    }

    // add ourselves
    totalWeight += root->weight;

    root->subtreeWeight = totalWeight;
    
    // printf ("rootID %d has subtreeWeight of %d\n", root->id, totalWeight);

    return totalWeight;
}




