#include "mymat.h"

int main(void) {
    char *comName, *comNameP; /* Used to hold command name. */
    char *comArgs, *comArgsP; /* Used to hold rest of command, which is the command arguments string. */
    char *line = malloc(sizeof(char) * MAX_LINE); /* Used to hold each command string received from input. */
    char *keep = line;  /* Keep initial index of line memory. */
    int found; /* To signal whether we identify command name from input. */
    int lineCount = 0; /* Used to determine memory reallocation. */

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
    struct command *comP; /* We use this pointer to traverse commands array. */
    int comLen = sizeof(commands) / sizeof(struct command); /* Calculate length of commands array safely. */

    /* Initialize matrices with 0.0 values, and matrix names. */
    Matrix mats[6] = {
            {"MAT_A", {{0}}},
            {"MAT_B", {{0}}},
            {"MAT_C", {{0}}},
            {"MAT_D", {{0}}},
            {"MAT_E", {{0}}},
            {"MAT_F", {{0}}},
    };

    /* In order to print prompt to screen, we determine if program is run from console or file redirection. */
    testTerminal();
    prompt(); /* print prompt to console if necessary. */

    /* Get input from user, and while input is received (one line at a time, ends with '\n'), do commands. */
    while (fgets(line, MAX_LINE, stdin)){
        lineCount++;
        if (line[strlen(line)-1] != '\n'){ /* Increase size of line, to accommodate rest of string, until '\n'. */
            keep = (char *) realloc(keep, ((lineCount+1) * MAX_LINE) * sizeof(char));
            line = keep + (lineCount * MAX_LINE) - 1; /* Reset line pointer, after reallocation to correct place. */
            continue; /* continue, to get rest of line into memory. */
        } else {  /* We finished getting whole line into memory. */
            if (strlen(keep) > MAX_LINE) /* If true, the whole line is more than MAX_LINE. */
                line = keep; /* Revert line pointer back to origin. */
        }

        /* Remove redundant white spaces, and convert first white space to ' ' for comfort. */
        if (trimString(line) == NULL){
            /* If NULL is returned, we have multiple consecutive commas, so we abort command */
            prompt(); /* print prompt to console if necessary. */
            continue;
        }

        /* In case we received empty line (just '\n'), simply print prompt, and handle next command line. */
        if (strcmp(line, "") == 0){
            prompt(); /* print prompt to console if necessary. */
            continue;
        }

        /* Now we have a line potentially like: "COMMAND_NAME ARG1,ARG2,..." */
        comName = strtok(line, " "); /* Take substring, before first white space. */

        /* If command ends with comma, we throw exception. */
        if (comName[strlen(comName)-1] == ','){
            printf("Illegal comma\n");
            prompt(); /* print prompt to console if necessary. */
            continue;
        }

        /* Take substring, after first white space. This string will be arguments for the command. */
        comArgs = strtok(NULL, " ");

        /* Handle stop condition for program. */
        if (strncmp(comName, "stop", 4) == 0){ /* Starts with 'stop'. */
            if (strlen(comName) == 4 && comArgs == NULL){ /* Valid stop command, bye bye. */
                free(keep);
                exit(0);
            }

            else { /* if command starts with stop, but has more characters or arguments, we throw. */
                printf("Extraneous text after end of command\n");
                prompt(); /* print prompt to console if necessary. */
                continue;
            }
        }

        /* Check if uppercase chars in command name */
        for (comNameP = comName; *comNameP != '\0'; comNameP++){
            if (isupper(*comNameP)){ /* Uppercase chars not allowed in command name, throw. */
                break;
            }
        }
        if (*comNameP != '\0'){
            printf("Uppercase chars not allowed in command name.\n");
            prompt();
            continue;
        }

        /* Check if lowercase chars in command args */
        if (comArgs != NULL){
            for (comArgsP = comArgs; *comArgsP != '\0'; comArgsP++){
                if (islower(*comArgsP)){ /* Lowercase chars not allowed in command args, throw. */
                    break;
                }
            }
            if (*comArgsP != '\0'){
                printf("Lowercase chars not allowed in command args.\n");
                prompt();
                continue;
            }
        }

        /* If no arguments are supplied, and command is not 'stop', we throw exception. */
        if (comArgs == NULL && strcmp(comName, "stop") != 0){
            printf("Missing argument\n");
            prompt(); /* print prompt to console if necessary. */
            continue;
        }

        /* Check if comma exists in args for all commands except print_mat, if not we throw message. */
        if (comArgs != NULL && strchr(comArgs, ',') == NULL && strcmp(comName, "print_mat") != 0){
            printf("Missing comma\n");
            prompt(); /* print prompt to console if necessary. */
            continue;
        }

        /* Look for function, by command name, if found, set 'found' to 1. */
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
            printf("Undefined command name\n"); /* Unrecognized command name, throw. */
        }

        prompt(); /* print prompt to console if necessary. */

        /* Reset line counter, and decrease memory size to MAX_LINE */
        lineCount = 0;
        keep = (char *) realloc(keep, ((lineCount+1) * MAX_LINE) * sizeof(char));
    }
    printf("Error: did not receive 'stop' command.\n");
    free(keep);
    return 1;
}
