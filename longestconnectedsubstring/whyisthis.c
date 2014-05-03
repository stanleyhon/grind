#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare (char * string, int sourceIndex, int targetIndex, int length) {
    while (length > 0) {
        if (string[sourceIndex] == string[targetIndex]) {
            sourceIndex++;
            targetIndex++;
            length--;
        } else {
            return 0;
        }
    }

    return 1;
}

int main (void) {
    char * string = "stanleys";

    int stringLength = strlen(string);

    int targetLength = stringLength - 1;

    int comparisonStringStart = 0;
    
    int targetStringStart = 0;
    
    while (targetLength > 0) { 
        // keep track of comparison string
        if (targetStringStart == comparisonStringStart) { 
            targetStringStart++;
        } 
        
        // compare string of length "targetLength"
        // starting at comparisonStringStart & targetStringStart
        if (compare (string, comparisonStringStart, targetStringStart, targetLength) == 1) {
            int j = 0;
            while (j < targetLength) {
                printf("%c", string[comparisonStringStart + j]);
                j++;
            }

            putchar('\n');
            return 0;
        }

        // target has no room to continue
        if (targetStringStart + 1 + targetLength > stringLength) {
            // start again
            targetStringStart = 0;
            // see if we can move comparison up one
            if (comparisonStringStart + 1 + targetLength <= stringLength) {
                comparisonStringStart++;
            // if not try smaller substring
            } else {
                targetLength--;
            }
        } else {
            targetStringStart++;
        }
    }

    return 0;
}
    





