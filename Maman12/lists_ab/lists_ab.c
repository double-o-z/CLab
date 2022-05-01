#include "lists_ab.h"

/* This program called lists_ab, does the following:
 * 0. Asks user for input.
 * 1. Gets unknown size array of characters, using realloc to increase array size, from stdin (user, file).
 * 2. Print array to output, as lines of fixed length (define LINE_LENGTH).
 * 3. Sum amount of input characters and sum amount of input alpha-numeric characters.
 * 4. Print both sums in an informative manner.
 */
int main() {
    char *listArr = (char *) malloc(LINE_LENGTH * sizeof(char)); /* First line memory allocation */
    char *keep = listArr;
    sumChars = sumAlphaNum = 0;

    printf("Please insert input:\n");
    while ((c = getchar()) != EOF){
        sumChars++;
        if (isalnum(c))
            sumAlphaNum++;
        if (sumChars % LINE_LENGTH == 0){ /* increase array size, we've reached limit */
            keep = (char *) realloc(keep, (sumChars + LINE_LENGTH) * sizeof(char));
            listArr = keep + sumChars;
        }
        *listArr++ = c;
    }

    if (sumChars % LINE_LENGTH == 0){ /* increase array size, we've reached limit */
        keep = (char *) realloc(keep, (sumChars + 1) * sizeof(char));
        listArr = keep + sumChars;
    }
    *++listArr = '\0';

    printLines(keep);
    return 0;
}

void printLines(char *keep){
    int i, charCount;
    printf("output:\n");
    for (i = charCount = 0; i < sumChars; i++, charCount++){
        if (*keep == '\n')
            charCount = 0;
        if ((charCount % LINE_LENGTH) == 0)
            printf("\n");
        printf("%c", *keep++);
    }
    printf("\n\n");
    printf("Sum of all chars: %d\n", sumChars);
    printf("Sum of all alpha-numeric chars: %d\n", sumAlphaNum);
}