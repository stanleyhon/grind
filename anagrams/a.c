#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int characters1[256];
int characters2[256];

int main (void) {
    char string1[1000];
    char string2[1000];

    fgets (string1, 1000, stdin);
    fgets (string2, 1000, stdin);
    
    int string1Length = strlen(string1);

    // we need to drop the stupid new line from the first string....
    string1Length--;
    string1[string1Length] = '\0';

    int string2Length = strlen(string2);

    if (string1Length != string2Length) {
        printf ("Not anagrams!");
        return EXIT_SUCCESS;
    }

    int idx = 0;
    while (idx < string1Length) {
        characters1[(int)string1[idx]]++;
        idx++;
    }

    idx = 0;
    while (idx < string2Length) {
        characters2[(int)string2[idx]]++;
        idx++;
    }

    // walk the two character arrays and make sure everythings the same
    idx = 0;
    while (idx < 256) {
        if (characters1[idx] != characters2[idx]) {
            printf ("Not anagrams!");
            return EXIT_SUCCESS;
        }
        idx++;
    }

    printf ("Anagrams!");

    return EXIT_SUCCESS;
}
