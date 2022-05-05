#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE 1000

typedef struct {
    float arr[4][4];
} mat;

void initMats(mat *mats[]);
void printMat(mat *MAT);
char *trimString(char *s);