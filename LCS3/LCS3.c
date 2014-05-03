#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int *** DP;

int LCS (char * A, size_t Alen, char * B, size_t Blen, char * C, size_t Clen);

int main (void) {

    char * A = "acbdefgh";
    size_t Alen = strlen(A);
    printf ("String %s is of length %zu\n", A, Alen);
    char * B = "adefhp";
    size_t Blen = strlen(B);
    printf ("String %s is of length %zu\n", B, Blen);
    char * C = "aef";
    size_t Clen = strlen(C);
    printf ("String %s is of length %zu\n", C, Clen);

    printf ("Apparently LCS is of length: %d\n", LCS (A, Alen, B, Blen, C, Clen));

    return EXIT_SUCCESS;
}

int LCS (char * A, size_t Alen, char * B, size_t Blen, char * C, size_t Clen) {
    if (A[Alen-1] == B[Blen-1] && B[Blen-1] == C[Clen-1]) {
        return LCS (A, Alen-1, B, Blen-1, C, Clen-1) + 1;
    } else {
        int reduceA = 0; 
        int reduceB = 0;
        int reduceC = 0;
        if (Alen > 1) {
            reduceA = LCS (A, Alen-1, B, Blen, C, Clen);
        }
        if (Blen > 1) {
            reduceB = LCS (A, Alen, B, Blen-1, C, Clen);
        }
        if (Clen > 1) {
            reduceC = LCS (A, Alen, B, Blen, C, Clen-1);
        }

        if (reduceA >= reduceB && reduceA >= reduceC) {
            assert (reduceA != -1);
            return reduceA;
        } else if (reduceB >= reduceA && reduceB >= reduceC) {
            assert (reduceB != -1);
            return reduceB;
        } else {
            assert (reduceC != -1);
            return reduceC;
        }
    }
    
    return -1;
}
