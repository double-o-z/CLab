#include "mat.h"

/* Return a pointer to the (shifted) trimmed string. */
char *trimString(char *s) {
    char *original = s;
    char *p = s;
    char *keep = s;
    size_t len = 0;

    /* remove leading white spaces. */
    while (isspace((unsigned char) *s)) {
        s++;
    }
    /* remove trailing white spaces. */
    if (*s) {
        while (*p) p++;
        while (isspace((unsigned char) *(--p)));
        p[1] = '\0';
        len = (size_t) (p - s + 1);
    }
    /* remove redundant white spaces in the middle. */
    if (*s){
        int firstSpace = 1;
        keep = p = s;
        while (*p){
            if (isspace((unsigned char) *p)){
                if (firstSpace == 1){
                    firstSpace--;
                }
                else {
                    while (isspace((unsigned char) *p))
                        p++;
                }
            }
            /* printf("char in s: %c, char is p: %c\n", *s, *p); */
            *s++ = *p++;
        }
        *s = '\0';
        s = keep;
    }
    return (s == original) ? s : memmove(original, s, len + 1);
}

/* get correct mat pointer */
Matrix *getMat(Matrix *mats, char *matName){
    int i;
    Matrix *matP = mats;
    for (i =0; i < 6; i++, matP++)  /* Get correct matrix */
        if (strcmp(matP->name, matName) == 0)
            break;
    return matP;
}

/* printMax: prints a matrix to console.
 * Gets argument matrix pointer */
void printMat(char *matName, Matrix *mats){
    int i, j;
    Matrix *matP = getMat(mats, matName);
    printf("Matrix %s:\n", matP->name);
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j){
            printf("%.2f\t", matP->arr[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void readMat(char *args, Matrix *mats){
    int i = 0, j = 0;
    char *valString;
    float val;
    Matrix *matP;
    char *matName = strtok(args, ",");
    matP = getMat(mats, matName);
    while ((valString = strtok(args, ","))){
        val = atof(valString);
        matP->arr[i][j++] = val;
        if (j == MAT_DIM){
            j = 0;
            i++;
        }
    }
}