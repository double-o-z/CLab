#include "mat.h"

int main() {
    char *comName;
    char *comArgs;
    char *line = malloc(sizeof(char) * MAX_LINE);
    int found;

    /* Initialize command struct array */
    struct command commands[] = {
            {"read_mat", readMat},
            {"print_mat", printMat},
            {"add_mat", addMats},
            {"sub_mat", subtractMats},
            {"mul_mat", multiplyMats},
            {"mul_scalar", multiplyMatByScalar},
            {"trans_mat", transposeMat}
    };
    struct command *comP = commands;
    int comLen = sizeof(commands) / sizeof(struct command);

    /* Initialize matrices with 0.0 values. */
    int i, j;
    Matrix mats[6] = {
            {"MAT_A"},
            {"MAT_B"},
            {"MAT_C"},
            {"MAT_D"},
            {"MAT_E"},
            {"MAT_F"},
    };
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

    /* Get input from user, and while input is received (one line at a time), do commands. */
    while (fgets(line, MAX_LINE, stdin)){
        trimString(line);
        /* Now we have a line like: COMMAND ARG1,ARG2,... */
        comName = strtok(line, " ");
        comArgs = strtok(NULL, " ");
        if (strcmp(comName, "stop") == 0)
            exit(0);
        /* printf("line: %s\n", line); */
        /* printf("command: %s\n", comName); */
        /* printf("args: %s\n", comArgs); */

        for (comP = commands, found = 0; (comP - commands) < comLen; comP++){
            if (strcmp(comP->name, comName) == 0){
                found = 1;
                break;
            }
        }

        if (found){
            comP->func(comArgs, mats);  /* comName is valid, lets run the proper command function. */
        } else {
            printf("Undefined command name\n");
        }
        /* processCommand(mats, command, args); */
    }
    return 0;
}
