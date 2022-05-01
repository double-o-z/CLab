#include "lists_ab.h"

/* Program lists_ab does the following:
 * 0. Gets text input from stdin (user of file redirection).
 * 1. Uses malloc and realloc to initialize and dynamically increase array size to store text.
 * 2. Prints array to output, as lines of fixed length (define LINE_LENGTH).
 * 3. Sums amount of input characters and amount of input alpha-numeric characters.
 * 4. Prints both sums in an informative manner.
 */
int main() {
    char *listArr = (char *) malloc(LINE_LENGTH * sizeof(char)); /* First line memory allocation */
    char *keep = listArr; /* keep first position of array, to use later for printing */
    sumChars = sumAlphaNum = 0; /* sum counters. */

    printf("Please insert characters input, end it with EOF character (Ctrl+D in Linux):\n");
    while ((c = getchar()) != EOF){
        sumChars++;
        if (isalnum(c))
            sumAlphaNum++;
        if (sumChars % LINE_LENGTH == 0){ /* increase array size, we've reached limit */
            keep = (char *) realloc(keep, (sumChars + LINE_LENGTH) * sizeof(char));
            listArr = keep + sumChars - 1; /* Necessary because address of next item might change! */
        }
        *listArr++ = c;
    }

    if (sumChars % LINE_LENGTH == 0){ /* increase array size by one if needed, do add '\0' char. */
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
    /* We use counter instead of looking for '\0' char because it could exist in some input files, this is safer. */
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