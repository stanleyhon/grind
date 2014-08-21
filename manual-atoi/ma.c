// "123" -> 124
// increment string integer by 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void) {
    char * input = malloc (sizeof (char) * 100);
    scanf ("%s", input);

    int index = strlen (input) - 1;

    int total = 0;
    int scalar = 1;
    while (index >= 0) {
        total += scalar * (input[index] - '0');
        scalar = scalar * 10;
        index--;
    }

    printf ("%d", ++total);

    return 0;
}

