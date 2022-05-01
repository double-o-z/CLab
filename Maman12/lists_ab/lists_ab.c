#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_LENGTH 8

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
    char c;
    int sumChars = 0, sumAlphaNum = 0;
    int i;

    printf("Please insert input:\n");

    while ((c = getchar()) != EOF){
        sumChars++;
        if (isalnum(c))
            sumAlphaNum++;
        if (sumChars % LINE_LENGTH == 0){ /* increase array size, we've reached limit */
            keep = realloc(keep, sumChars + LINE_LENGTH);
        }
        *listArr++ = c;
    }
    if (sumChars % LINE_LENGTH == 0){ /* increase array size, we've reached limit */
        listArr = realloc(listArr, sumChars + 1);
    }
    *listArr = '\0';
    for (i = 0; i < sumChars; i++){
        if (i % LINE_LENGTH == 0)
            printf("\n");
        printf("%c", *keep++);
    }
    printf("output: %s\n", keep);
    printf("sum of all chars: %d\n", sumChars);
    printf("sum of all alpha-numeric chars: %d\n", sumAlphaNum);
    return 0;
}
