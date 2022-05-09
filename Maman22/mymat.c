#include "mat.h"

int main(void) {
    char *comName; /* Used to hold command name. */
    char *comArgs; /* Used to hold rest of command, which is the command arguments string. */
    char *line = malloc(sizeof(char) * MAX_LINE); /* Used to hold each command string received from input. */
    int found; /* To signal whether we identify command name from input. */
    int terminal = 0; /* To signal whether to print prompt, before every command input. */

    /* Initialize command struct array, to be used to match command string to function. */
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

    /* Initialize matrices with 0.0 values, and matrix name. */
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

    if ((terminal = isatty(fileno(stdin))))
        printf(">>"); /* print prompt to console. */

    /* Get input from user, and while input is received (one line at a time), do commands. */
    while (fgets(line, MAX_LINE, stdin)){
        trimString(line); /* Remove redundant white spaces. */
        /*printf("line: %s\n", line);*/
        if (strcmp(line, "") == 0){
            if (terminal)
                printf(">>"); /* print prompt to console. */
            continue;
        }
        /* Now we have a line like: COMMAND ARG1,ARG2,... */
        comName = strtok(line, " "); /* Take substring, before first white space. */
        comArgs = strtok(NULL, " "); /* Take substring, after first white space. */
        if (strcmp(comName, "stop") == 0)
            exit(0);

        /*printf("command: %s\n", comName);*/
        /*printf("args: %s\n", comArgs);*/

        /* Look for function, by command string, if found, set 'found' to 1. */
        for (comP = commands, found = 0; (comP - commands) < comLen; comP++){
            if (strcmp(comP->name, comName) == 0){
                found = 1;
                break;
            }
        }

        /* If 'found' is 1, we call the function with the args string. */
        if (found){
            comP->func(comArgs, mats);  /* comName is valid, lets run the proper command function. */
        } else {
            printf("Undefined command name\n");
        }
        if (terminal)
            printf(">>"); /* print prompt to console. */
    }
    return 0;
}
