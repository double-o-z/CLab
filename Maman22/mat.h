#include <stdio.h>
#include <ctype.h>

typedef struct {
    float arr[4][4];
} mat;

void initMats(mat *mats[]);
void printMat(mat *MAT);