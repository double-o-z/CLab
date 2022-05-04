#include "mat.h"

int main() {
    /* Declare matrices, and matrices pointer array. */
    mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;
    mat *mats[] = {&MAT_A, &MAT_B, &MAT_C, &MAT_D, &MAT_E, &MAT_F};
    char c;

    /* Initialize matrices with 0.0 values. */
    initMats(mats);

    /* Test print MAT_A */
    printMat(&MAT_A);

    /* Get input from user, and while input is received (one line at a time), do commands. */
    while ((c = getchar()) != EOF){
        if (isspace(c))
            while (isspace(c = getchar()))
                ; /* skip preceding white spaces. */
        /* parse command name */
        
    }
    return 0;
}
