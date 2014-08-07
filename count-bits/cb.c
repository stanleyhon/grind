#include <stdio.h>
#include <stdlib.h>

int count_bits (int val);
int count_nonset_bits (int val);

int main (void) {

    int num;
    scanf ("%d", &num);

    printf ("set: %d\n", count_bits (num));
    printf ("unset : %d\n", count_nonset_bits (num));

    return EXIT_SUCCESS;
}

int count_bits (int val) {
    int total = 0;
    int shift = 0;
    while (shift < 32) {
        if ((val & (1 << shift)) != 0) {
            total++;
        }
        shift++;
    }

    return total;
}

int count_nonset_bits (int val) {
    return (32 - count_bits(val));
}
