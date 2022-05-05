#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE 1000
#define MAT_DIM 4

typedef struct {
    char name[5];
    float arr[MAT_DIM][MAT_DIM];
} Matrix;

struct command {
    char *name;
    void (*func)(char * args, Matrix *mats);
};

char *trimString(char *s);
Matrix *getMat(Matrix *mats, char *matName);

void readMat(char *args, Matrix *mats);
void printMat(char *args, Matrix *mats);