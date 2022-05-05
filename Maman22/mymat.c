#include "mat.h"

int main() {
    char *command;
    char *args;
    char *line = malloc(sizeof(char) * MAX_LINE);

    /* Initialize matrices with 0.0 values. */
    struct matObj mats[6];
    initMats(mats);

    /* Get input from user, and while input is received (one line at a time), do commands. */
    while (fgets(line, MAX_LINE, stdin)){
        trimString(line);
        printf("line: %s\n", line);
        /* Now we have a line like: COMMAND ARG1,ARG2,... */
        command = strtok(line, " ");
        args = strtok(NULL, " ");
        printf("command: %s\n", command);
        printf("args: %s\n", args);
        /* processCommand(mats, command, args); */
    }
    return 0;
}
