#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int string_reverse(char * string, int numChars) {
    // printf("string_reverse %d\n", numChars);

    int leftHandIndex = 0;
    int rightHandIndex = numChars - 1; // index

    while (rightHandIndex > leftHandIndex) {
        char temp = string[leftHandIndex];
        string[leftHandIndex] = string[rightHandIndex];
        string[rightHandIndex] = temp;

        leftHandIndex++;
        rightHandIndex--;
    }

    return 0;
}

int sentence_reverse(char * sentence, int sentenceLength) {
    int headIndex = 0;
    int tailIndex = 0;

    while (headIndex < sentenceLength && tailIndex < sentenceLength) {
        if (sentence[tailIndex] == ' ') {
            tailIndex++;
        } else {
            // we found the start of a word, find the end
            while (headIndex + 1 < (sentenceLength) && sentence[headIndex + 1] != ' ' &&
                    sentence[headIndex + 1] != '\0') {
                headIndex++;
            } // we found the end of the word

            // call string_rev on it
            string_reverse(sentence + tailIndex, headIndex - tailIndex + 1);

            tailIndex = headIndex + 1;
            headIndex++;
        }
    }
    return 0;
}





int main (void) {
    char * string = malloc(sizeof(char) * 150);
    memset(string, 32, 150);

    printf("Enter up to 149 characters: ");
    gets(string);

    printf("read: %s\n", string);
    printf("reversing...\n");

    // reverse
    sentence_reverse(string, 150);

    printf("reversed: %s\n", string);

    return 0;
}
