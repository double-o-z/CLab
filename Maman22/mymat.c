#include "mat.h"

int main() {
    /* Declare matrices, matrices pointer array, line string. */
    mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;
    mat *mats[] = {&MAT_A, &MAT_B, &MAT_C, &MAT_D, &MAT_E, &MAT_F};
    char c;
    char *line = malloc(sizeof(char) * MAX_LINE);

    /* Initialize matrices with 0.0 values. */
    initMats(mats);

    /* Test print MAT_A */
    printMat(&MAT_A);

    /* Get input from user, and while input is received (one line at a time), do commands. */
    while (fgets(line, MAX_LINE, stdin)){
        trimString(line);
        printf("line: %s\n", line);
        
    }
    return 0;
}
