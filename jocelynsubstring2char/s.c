#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int memo[26][26];
int startIndex[26][26];
int main (void) {
    char * s = malloc (5000000);
    assert (s != NULL);

    scanf ("%s", s);

    char * alphabet = "abcdefghijklmnopqrstuvwxyz";

    int idx = 0;
    while (idx < 26) {
        memset (memo, -1, sizeof (int) * 26);
        idx++;
    }

    int firstIdx = 0;
    int secondIdx = 0;

    while (firstIdx < 26) {
        secondIdx = 0;
        while (secondIdx < 26) {
            if (secondIdx == firstIdx) {
                secondIdx++;
                continue;
            }
            // substring 'a' 'b' is the same as 
            // substring with 'b' 'a'.
            // if either are memo'd before, don't recalc
            if (memo[firstIdx][secondIdx] != -1 &&
                memo[secondIdx][firstIdx] != -1) {
                secondIdx++;
                continue;
            }
            
            assert (secondIdx < 26);
            // we know we haven't done this before.
            int maxCountedStart = 0;
            int maxCounted = 0;
            int tempCounted = 0;
            int tempCountedStart = 0;
            int currentlyCounting = 0;

            int currentPosition = 0;
            while (currentPosition < strlen (s) - 1) { // subtract 1 to go from length to index
                if (s[currentPosition] == alphabet[firstIdx] || s[currentPosition] == alphabet[secondIdx]) {

                    if (currentlyCounting == 0) {
                        currentlyCounting = 1;
                        tempCountedStart = currentPosition;
                    }             

                    tempCounted++;
                } else {
                    // finished a string
                    if (tempCounted >= maxCounted) {
                        maxCounted = tempCounted;
                        maxCountedStart = tempCountedStart;
                    }

                    currentlyCounting = 0;
                    tempCounted = 0;
                    tempCountedStart = 0;
                }
                currentPosition++;
            }
            // need to check the case where the longest string goes to the end of the string.
            if (tempCounted >= maxCounted) {
                maxCounted = tempCounted;
                maxCountedStart = tempCountedStart;
            }
            
            memo[firstIdx][secondIdx] = maxCounted;
            memo[secondIdx][firstIdx] = maxCounted;
            startIndex[firstIdx][secondIdx] = maxCountedStart;
            startIndex[secondIdx][firstIdx] = maxCountedStart;

            secondIdx++;
        }

        firstIdx++;
    }

    printf ("Finished!\n");

    // now look for the largest in memo
    int largestValue = 0;
    int largestX = 0;
    int largestY = 0;

    firstIdx = 0;
    secondIdx = 0;
    while (firstIdx < 26) {
        secondIdx = 0;
        while (secondIdx < 26) {
            if (memo[firstIdx][secondIdx] >= largestValue) {
                largestValue = memo[firstIdx][secondIdx];
                largestX = firstIdx;
                largestY = secondIdx;
            }
            secondIdx++;
        }
        firstIdx++;
    }

    printf ("Longest was %d\n", largestValue);
    printf ("Starting from index %d\n", startIndex[largestX][largestY]);

    return EXIT_SUCCESS;
}


        


