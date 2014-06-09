#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void) {
    char * string = malloc (1000);
    scanf ("%s", string);

    int insertIndex;
    scanf ("%d", &insertIndex);

    char * insertString = malloc (1000);
    scanf ("%s", insertString);

    int stringLength = strlen(string);
    if (insertIndex <= 0) {
        printf ("%s%s", insertString, string);
    } else if (insertIndex >= stringLength) {
        printf ("%s%s", string, insertString);
    }

    int idx = 0;
    while (idx < stringLength) {
        printf ("%c", string[idx]);
        if (idx == insertIndex) {
            printf ("%s", insertString);
        }
        idx++;
    }

    printf ("\n");
    return EXIT_SUCCESS;
}

