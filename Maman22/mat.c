#include "mat.h"

/* initMats: initializes all 6 matrices with 0.0 values.
 * Gets argument matrices pointer array. */
void initMats(mat *mats[]){
    int i, j;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j){
            mats[0]->arr[i][j] = 0.0;
            mats[1]->arr[i][j] = 0.0;
            mats[2]->arr[i][j] = 0.0;
            mats[3]->arr[i][j] = 0.0;
            mats[4]->arr[i][j] = 0.0;
            mats[5]->arr[i][j] = 0.0;
        }
    }
}

/* printMax: prints a matrix to console.
 * Gets argument matrix pointer */
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