// A graph representation interface

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct graph * Graph;

typedef struct node * Node;

typedef struct node_set * Nodeset;

Graph newGraph (void);

// provided a list of nodes that can reach the new node &
// a list of nodes that this new node goes to.
// Inserts a new node.
Node addNode (Graph g, Nodeset goesTo, Nodeset comesFrom);

// Delete Node
void deleteNode (Graph g, Node n);

// Returns a list of all nodes
Nodeset listNodes (Graph g);

// Returns connections to the supplied node
Nodeset routesToN (Graph g, Node n);

// Returns connections from the supplied node
Nodeset routesFromN (Graph g, Node n);

// Given an array of nodes, creates a nodeset
Nodeset nodeSet (Node * nodelist, size_t num);

// query a nodeset
size_t nodeSetSize (Nodeset ns);
Node nodeGetIndex (Nodeset ns, int idx);

// Same node?
int sameNode (Node n1, Node n2);
