#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10
#define MAX_QUEUE_LENGTH 1000

struct queue {
    struct node * array[MAX_QUEUE_LENGTH];
    int start;
    int end;
};

struct stack {
    struct node * stack[MAX_QUEUE_LENGTH];
    int end;
};

struct node {
    struct node ** children;
    int payload;
};

struct node * newNode (int payload) {
    struct node * new = malloc (sizeof (struct node));
    new->children = malloc (sizeof (struct node *) * MAX_CHILDREN);
    memset (new->children, 0, MAX_CHILDREN);
    new->payload = payload;
    return new;
}


void addNode (struct node * root, int payload) {
    struct node * new = newNode (payload);
    int idx = 0;
    while (idx < MAX_CHILDREN) {
        if (root->children[idx] == NULL) {
            root->children[idx] = new;
            break;
        } else {
            idx++;
        }
    }

    return;
}

void enqueue (struct queue * q, struct node * ptr) {
    q->array[q->end] = ptr;
    if (q->end == MAX_QUEUE_LENGTH - 1) {
        q->end = 0;
    } else {
        q->end++;
    }
    return;
}

struct node * dequeue (struct queue * q) {
    struct node * ret = q->array[q->start];
    q->array[q->start] = 0;
    q->start++;
    if (q->start == MAX_QUEUE_LENGTH) {
        q->start = 0;
    }
    return ret;
}

struct node * pop (struct stack * s) {
    struct node * result = s->stack[s->end-1];
    s->end--;
    return result;
}

void push (struct stack * s, struct node * ptr) {
    s->stack[s->end++] = ptr;
}

int main (void) {

    struct queue queue;
    memset (queue.array, 0, MAX_QUEUE_LENGTH);
    queue.start = 0;
    queue.end = 0;

    struct node * new = newNode (1);
    addNode (new, 2);
    addNode (new, 2);
    addNode (new, 2);
    addNode (new, 2);
    addNode (new, 2);
    addNode (new, 2);
    addNode (new, 2);
    addNode (new, 2);
    addNode (new, 2);
    addNode (new, 2);
    addNode (new, 2);

    int payload = 13;
    int childNumber = 0;
    while (childNumber < 10) {
        addNode (new->children[childNumber], payload);
        addNode (new->children[childNumber], payload);
        payload++;
        childNumber++;
    }

    // BFS
    enqueue (&queue, new);
    while (queue.start != queue.end) {
        struct node * target = dequeue (&queue);
        printf ("looking at %d\n", target->payload);
        int idx = 0;
        while (idx < MAX_CHILDREN) {
            if (target->children[idx] != NULL) {
                enqueue (&queue, target->children[idx]);
            }
            idx++;
        }
    } 

    printf ("****************************\n");

    // DFS
    struct stack s;
    s.end = 0;
    memset (s.stack, 0, 1000);
    push (&s, new);

    while (s.end != 0) {
        struct node * target = pop (&s);
        printf ("looking at %d\n", target->payload);
        int idx = 0;
        while (idx < MAX_CHILDREN) {
            if (target->children[idx] != NULL) {
                push (&s, target->children[idx]);
            }
            idx++;
        }
    }

    return EXIT_SUCCESS;
}
