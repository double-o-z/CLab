#include "mat.h"

int main() {
    /* Declare matrices, and matrices pointer array. */
    mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;
    mat *mats[] = {&MAT_A, &MAT_B, &MAT_C, &MAT_D, &MAT_E, &MAT_F};
    char c;
    char *line;
    char *keep;
    char *command;

    /* Initialize matrices with 0.0 values. */
    initMats(mats);

    /* Test print MAT_A */
    printMat(&MAT_A);

    /* Get input from user, and while input is received (one line at a time), do commands. */
    while ((c = getchar()) != EOF){
        do {
            *line++ = c; /* Gather characters for a command. */
        } while ((c = getchar()) != '\n');
        *line = '\0';
        /* Now we have a command, lets parse it. */
        /* Separate by delim " "
         * We should check number of results:
         * 1. if result == "stop", do stop().
         * 2. else separate by delim ","
         *  2.1 then check matrix string by metrices array.*/
    }
    return 0;
}
