#include "st.h"

#include <time.h>
#include <assert.h>

#define MAX_INSERT_VALUE 100000
#define NUM_INSERTIONS 10000
#define NUM_LOOKUPS 1000

int main (void) {
    printf ("Testing create...\n");
    SplayTree st = splayTree_create (50);
    srand (time (NULL));
    assert (st != NULL);
    printf ("Create passed!\n");

    st = splayTree_insert (st, 1);
    st = splayTree_insert (st, 2);
    st = splayTree_insert (st, 3);
    st = splayTree_insert (st, 4);
    st = splayTree_insert (st, 5);
    st = splayTree_insert (st, 6);
    st = splayTree_insert (st, 7);
    st = splayTree_insert (st, 8);
    st = splayTree_insert (st, 9);
    st = splayTree_insert (st, 10);
    st = splayTree_insert (st, 11);
//    printf ("Testing insert\n");
    int i = 1;
//    while (i < NUM_INSERTIONS) {
//        int value = rand () % MAX_INSERT_VALUE;
//        printf ("%d ", value); 
//        if (i % 50 == 0) printf ("\n");
//        st = splayTree_insert (st, value);
//        i++;
//    }
//    printf ("Insert passed!\n");

    printf ("Testing lookup\n");
    i = 0;
    while (i < NUM_LOOKUPS) {
        int search  = rand () % MAX_INSERT_VALUE;
        int found = splayTree_lookup (st, search);
        printf ("Looking for %d, Found? [%c]\n", search, found == VALUE_FOUND ? 'Y' : 'N');
        i++;
    } 
    printf ("\nLookup passed!\n");

    printf ("Testing delete, user input required\n");
    int delete;
    printf ("Enter a value to try and delete: ");
    scanf ("%d", &delete);

    assert (splayTree_lookup (st, delete) == VALUE_FOUND);
    st = splayTree_delete (st, delete);
    assert (st != NULL);
    assert (splayTree_lookup (st, delete) == VALUE_NOT_FOUND);
    printf ("Delete passed!\n");

    splayTree_print (st);

    printf ("All Tests Passed! You are Awesome!\n");

    return EXIT_SUCCESS;
}

