#include "gr.h"

int main (void) {
    printf ("Testing newGraph\n");
    Graph g = newGraph ();
    printf ("Passed!\n");

    printf ("Testing addNode\n");
    Node node1 = addNode (g, NULL, NULL);
    assert (node1 != NULL);
    printf ("Passed!\n");

    printf ("Testing nodesets\n");
    Nodeset ns = nodeSet (&node1, 1);
    assert (ns != NULL);
    Node node2 = addNode (g, ns, ns);
    assert (node2 != NULL);
    printf ("Passed!\n");

    Nodeset allNodes = listNodes (g);

    printf ("There are apparently %zu nodes in the graph\n", nodeSetSize (allNodes));

    printf ("Checking RoutesTo\n");
    Nodeset nodesThatReachNode1 = routesToN (g, node1);
    assert (nodeSetSize (nodesThatReachNode1) == 1); 
    Nodeset nodesThatReachNode2 = routesToN (g, node2);
    assert (nodeSetSize (nodesThatReachNode2) == 1); 

    printf ("Checking RoutesFrom\n");
    Nodeset nodesOutFromNode1 = routesFromN (g, node1);
    assert (nodeSetSize (nodesOutFromNode1) == 1);
    Nodeset nodesOutFromNode2 = routesFromN (g, node2);
    assert (nodeSetSize (nodesOutFromNode2) == 1);

    printf ("Checking getIndex\n");
    Node node1copy = nodeGetIndex (nodesThatReachNode2, 0);
    assert ((sameNode (node1copy, node1) == 1));

    Node node2copy = nodeGetIndex (nodesThatReachNode1, 0);
    assert ((sameNode (node2copy, node2) == 1));

    printf ("Testing delete\n");
    deleteNode (g, node2copy);

    Nodeset node1Nodeset = routesToN (g, node1);
    assert (nodeSetSize (node1Nodeset) == 0);

    printf ("All Tests Passed! You are Awesome!\n");

    return EXIT_SUCCESS;
}

