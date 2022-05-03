#include "mymat.h"

/* utility function that prints all values of the given matrix.
 * takes pointer for matrix, and prints all of its values, each row in a separate line. */
void printMat(mat *MAT){
    int i, j;
    printf("MAT:\n");
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j){
            printf("%f ", MAT->arr[i][j]);
        }
        putchar('\n');
    }
}