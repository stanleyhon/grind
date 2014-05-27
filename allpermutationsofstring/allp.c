#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_RESULTS 50000

int listLength;
char ** list;

int workingListLength;
char ** workingList;

void printList (void) {
    int i = 0;
    while (i < listLength) {
        printf ("%s\n", list[i]);
        i++;
    }
    return;
}

// given a string interleaves the string with the 
// interleave character and inserts them into the
// global list

// also removes the string from the global list
void interleave (char * string, char interleave, int firstCall) {
    //printf ("interleave called with %s\n", string);
    char temp[100];
    strcpy (temp, string);
    //printf ("interleave saved string called %s\n", temp);

    if (firstCall == 1) {
        // setup the global working list
        workingList = malloc (sizeof (char*) * MAX_RESULTS);
    }

    // now. for the saved string called temp
    // interleave it.
    int stringLength = strlen (temp);
    //printf ("The length of it is %d\n", stringLength);

    int interleaveLocation = 0;
    while (interleaveLocation <= stringLength) {
        workingList[workingListLength] = malloc (stringLength + 1);
        int workingListIdx = 0;
        int tempIdx = 0;
        while (tempIdx <= stringLength) {

            // if we're working on the interleave location
            // copy the interleave there
            if (tempIdx == interleaveLocation) {
                workingList[workingListLength][workingListIdx] = interleave;
                workingListIdx++;
            }

            // if tempIdx is not the very last place, where the null term should be
            // copy as usual
            if (tempIdx != stringLength) { 
                workingList[workingListLength][workingListIdx] = temp[tempIdx];
                workingListIdx++;

            // if it is, put a null term
            } else {
                workingList[workingListLength][workingListIdx] = '\0';
                workingListIdx++;
            }
            tempIdx++;
        }
        workingListLength++;
        interleaveLocation++;
    }
    //printf ("interleave finished\n");
    return;
}

void permute (char * string, int length) {
    if (length == 1) {
        list[listLength] = malloc (100);
        strcpy (list[listLength], string);
        listLength = 1;
        //printf ("permute finished....\n\n");
        return;
    }

    // if it's not length 1
    // permute it locking in this first character
    // interleave the first character into the global list
    //printf ("permuting on %s with length %d\n", string+1, length-1);
    permute (string+1, length-1);

    // now for all those permutations,
    // interleave our character with all the permutations
    int globalIdx = 0;
    char interleaver = string[0];
    while (globalIdx < listLength) {
        int firstCall = 0;
        if (globalIdx == 0) firstCall = 1;
        //printf ("calling interleave with %s interleaving char %c\n", list[globalIdx], interleaver);
        interleave (list[globalIdx], interleaver, firstCall);
        globalIdx++;
    }

    // replace global list with working list
    free (list);
    list = workingList;
    listLength = workingListLength;
    workingListLength = 0;

    //printf ("permute finished....\n\n");
    return;
}


int main (int argc, char * argv[]) {
    char * string = argv[1];

    if (strlen (string) > 8) {
        printf ("i don't ahve enough memory to do that.\n");
        return 1;
    }

    list = malloc (sizeof (char*) * MAX_RESULTS);

    permute (string, strlen(string));

    printList ();

    return EXIT_SUCCESS;
}
