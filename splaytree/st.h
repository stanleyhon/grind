#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define VALUE_FOUND 1
#define VALUE_NOT_FOUND 0 

typedef struct splaytree * SplayTree;

SplayTree splayTree_create (int value);
SplayTree splayTree_insert (SplayTree st, int value);
SplayTree splayTree_delete (SplayTree st, int value);
void splayTree_print (SplayTree st);
int splayTree_lookup (SplayTree st, int value);
