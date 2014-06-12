// inprogress. this seems to straight forward and i know how to 
// do this so i'm probably going to try and focus on
// adjacency matrix and incidence matrix

#include "gr.h"

struct node {
    struct llNode * root;
    int payload;
    uint32_t uuid;
};

struct node_set {
    struct node ** set;
    int length;
};  

struct llNode {
    struct llNode * next;
    struct node * payload;
};

struct graph {
    // use a linked list
    struct llNode * root;
    uint32_t uuid_next;
};

Graph newGraph (void) {
    Graph g = malloc (sizeof (struct graph));
    g->root = NULL;
    return g;
}

// provided a list of nodes that can reach the new node &
// a list of nodes that this new node goes to.
// Inserts a new node.
Node addNode (Graph g, Nodeset goesTo, Nodeset comesFrom) {
    // make a node first
    Node n = malloc (sizeof (struct node));
    n->payload = 0xDEADBEEF;
    n->uuid = g->uuid_next;
    g->uuid_next++;

    // setup it's outoging edges.
    int idx = 0;
    while (goesTo != NULL && idx < goesTo->length) {
        // make a new node
        struct llNode * newNode = malloc (sizeof (struct llNode));
        newNode->next = NULL;
        newNode->payload = goesTo->set[idx];
        
        // figure out where the end of the list is
        struct llNode * feeler = n->root;
        if (feeler != NULL) {
            while (feeler->next != NULL) {
                feeler = feeler->next;
            }
            // put it there
            feeler->next = newNode;
        } else {
            n->root = newNode;
        }
        
        idx++;
    }

    // setup ingoing.
    // for each coming from, add the new node.
    idx = 0;
    while (comesFrom != NULL && idx < comesFrom->length) {
        // find the end in the target node's list
        struct llNode * feeler = comesFrom->set[idx]->root;
        
        // make the new node we're going to put on the list
        struct llNode * newNode = malloc (sizeof (struct llNode));
        newNode->payload = n; // hook it up the node we made earlier
        newNode->next = NULL;

        if (feeler == NULL) {
            // connect it to root
            comesFrom->set[idx]->root = newNode;
        } else {
            // look for the end and connect the node there
            while (feeler->next != NULL) {
                feeler = feeler->next;
            }
            feeler->next = newNode;
        }
        idx++;
    }

    return n;
}


// Delete Node
void deleteNode (Graph g, Node n) {
    
    return;
}

// Returns a list of all nodes
Nodeset listNodes (Graph g) {
    return NULL;
}

// Returns connections to the supplied node
Nodeset routesToN (Graph g, Node n) { 
    return NULL;
}

// Returns connections from the supplied node
Nodeset routesFromN (Graph g, Node n) {
    return NULL;
}

// Given an array of nodes, creates a nodeset
Nodeset nodeSet (Node * nodelist, size_t num) {
    Nodeset new = malloc (sizeof (struct node_set));
    new->set = malloc (sizeof (struct node *) * num);
    int idx = 0;
    while (idx < num) {
        new->set[idx] = nodelist[idx];
        idx++;
    }
    return new;
}

// query a nodeset
size_t nodeSetSize (Nodeset ns) {
    return ns->length;
}

Node nodeGetIndex (Nodeset ns, int idx) {
    return NULL;
}

// Same node?
int sameNode (Node n1, Node n2) {
    return 0;
}
