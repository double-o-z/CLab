#include "mat.h"

/* initMats: initializes all 6 matrices with 0.0 values.
 * Gets argument matrices pointer array. */
void initMats(struct matObj mats[]){
    int i, j;
    char c;
    struct matObj *matP = mats;
    for (i = 0; i < 6; i++) {
        c = 'A' + (matP-mats);
        matP++;
        printf("matP.name: %s\n", matP->name);
        printf("c: %c\n", c);
    }
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j){
            mats[0].arr[i][j] = 0;
            mats[1].arr[i][j] = 0;
            mats[2].arr[i][j] = 0;
            mats[3].arr[i][j] = 0;
            mats[4].arr[i][j] = 0;
            mats[5].arr[i][j] = 0;
        }
    }
}

/* printMax: prints a matrix to console.
 * Gets argument matrix pointer */
void printMat(char *mat, struct matObj *mats){
    int i, j;
    struct matObj *matP = mats;
    for (; strcmp(matP->name, mat); matP++)
        ;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j){
            printf("%f ", matP->arr[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

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

void processCommand(struct matObj mats[], char *command, char *args){
    struct matObj *pCase = mats;
    for (; pCase; pCase++){
        if (strcmp(pCase->name, command) == 0) {
            (*pCase->func)(args);
            break;
        }
    }

}