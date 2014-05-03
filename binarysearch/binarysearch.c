#include <stdio.h>
#include <stdlib.h>

int main () {
    int num;
    scanf("%d", &num);

    int * arr = malloc(num*sizeof(int));

    int i;
    while (i < num) {
        scanf("%d", arr + i);
        i++;
    }

    printf("what do you want to look for: ");
    int lookFor;
    scanf("%d", &lookFor);

    // sort list
    int pivot;
    int low = 0;
    int high = num - 1;

    int found = 0;
    while (found == 0) {
        if ((low - high) * -1 == 1) { // corner case
            if (arr[low] == lookFor) {
                printf("found it at position %d\n", low);
                break;
            } else if (arr[high] == lookFor) {
                printf("found it at position %d\n", high);
                break;
            } else {
                printf("couldn't find it...\n");
                found = 1;
            }
        }
        pivot = low + ((high - low) / 2);
        if (arr[pivot] == lookFor) {
            printf ("found it at position %d\n", pivot);
            break;
        } else {
            if (arr[pivot] > lookFor) {
                printf ("high now %d\n", high);
                high = pivot;
            } else if (arr[pivot] < lookFor) {
                printf ("low now %d\n", low);
                low = pivot;
            }
        }
             
    }

    return 0;
}
