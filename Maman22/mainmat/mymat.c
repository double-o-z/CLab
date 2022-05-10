#include "mymat.h"

/* To signal whether to print prompt, before every command input. */
int terminal;

/* trimString: returns a pointer to the (shifted) trimmed string.
 * Removes all leading and trailing white spaces,
 * and all white spaces between command and arguments (except for the first one).
 * Example: "    read_mat   MAT_A,  1,2  ,  3   "
 * Result: "read_mat MAT_A,1,2,3" */
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
        int firstComma = 1;
        keep = p = s;
        while (*p){
            if (isspace((unsigned char) *p)){
                if (firstSpace){
                    *p = ' '; /* replace tab with white space for comfort. */
                    firstSpace--;
                }
                else {
                    while (isspace((unsigned char) *p))
                        p++;
                }
            }
            /* Check for multiple consecutive commas */
            if (*p == ','){
                if (firstComma){
                    firstComma--;
                } else {
                    printf("Multiple consecutive commas\n");
                    return NULL;
                }
            } else {
                firstComma = 1;
            }
            /* printf("char in s: %c, char is p: %c\n", *s, *p); */
            *s++ = *p++;
        }
        *s = '\0';
        s = keep;
    }
    return (s == original) ? s : memmove(original, s, len + 1);
}

/* getMat: returns a pointer to given matrix name. */
Matrix *getMat(Matrix *mats, char *matName){
    int i;
    Matrix *matP = mats;
    for (i =0; i < 6; i++, matP++)  /* Get correct matrix */
        if (strcmp(matP->name, matName) == 0)
            break;
    if (matP - mats > 5) { /* Didn't find matrix by name. */
        printf("Undefined matrix name\n");
        return NULL;
    }
    return matP;
}

/* testTerminal: determines if program runs from console or file redirection.
 * Sets terminal to True if it runs from console, and False if it runs from file redirection. */
void testTerminal(void){
    terminal = isatty(fileno(stdin));
}

/* prompt: prints '>>' to console, if program runs on console and not file redirection. */
void prompt(){
    if (terminal)
        printf(">>"); /* print prompt to console. */
}

/* printMax: prints a matrix to console.
 * Gets argument matrix pointer */
void printMat(char *matName, Matrix *mats){
    int i, j;
    Matrix *matP = getMat(mats, matName); /* First fetch the matrix by name. */
    if (matP == NULL) /* Exception was already thrown by getMat, lets return. */
        return;
    printf("\n\t\t**** %s ****\n", matP->name);  /* Print matrix name */
    for (i = 0; i < 4; ++i) {
        putchar('\t'); /* Tab at beginning of every row. */
        for (j = 0; j < 4; ++j){
            printf("%7.2f\t", matP->arr[i][j]);  /* print double value, with precision 2, and tab. */
        }
        putchar('\n');
    }
    putchar('\n');
}

/* readMat: sets values to a given matrix.
 * Gets arguments: MATRIX_NAME,VAL1,VAL2,...
 * (sets between 0 to 16 values, by order of input). */
void readMat(char *args, Matrix *mats){
    int i = 0, j = 0, argsCount = 0, foundArg = 0;
    char *valString, *endOfString, *matName, last;
    double val, tempArr[4][4] = {0}; /* temp array to hold values. */
    Matrix *matP;

    last = args[strlen(args)-1]; /* get last char in args */
    matName = strtok(args, ","); /* matrix name. */
    matP = getMat(mats, matName); /* fetch matrix by name. */

    /* if not found exception was thrown in getMat. */
    if (matP == NULL)
        return;

    /* If last char of args is not alphanumeric (after white space trim), we cancel command. */
    if (!isalnum(last)){
        printf("Extraneous text after end of command\n");
        return;
    }

    /* Iterate over all potential args values. */
    while (argsCount++ < MAT_DIM * MAT_DIM){
        val = 0.0; /* in case no more values exist in args, we send value 0.0 as default. */
        if ((valString = strtok(NULL, ",")) != NULL) {
            /* If valString is not null, we found a value, lets set foundArg to True */
            if (!foundArg)
                foundArg = 1;
            val = strtod(valString, &endOfString); /* Convert valString to double */
            /* If valString had chars other than digits, we throw. */
            if (endOfString - valString != strlen(valString)){
                printf("Argument is not a real number\n");
                return; /* Cancel this command, by returning without setting the matrix. */
            }
        } else { /* No more values in args. */
            if (!foundArg){  /* If we got here, it means 'strtok' returned NULL on the first time, so we cancel. */
                printf("Missing argument\n");
                return;
            }
        }
        /* If we got here, we should set tempArr with the parsed value. */
        tempArr[i][j++] = val;
        /* Increment column until end of column, and then increment row, and reset column. */
        if (j == MAT_DIM){
            j = 0;
            i++;
        }
    }
    /* Only if all arguments are valid doubles, we insert into the matrix. */
    /* If even one of the arguments is invalid, the function would return without changing the matrix. */
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j)
            matP->arr[i][j] = tempArr[i][j]; /* we copy each value because tempArr is automatic array. */
    }
}

/* operandMats: utility function that serves functions: addMat, subMat, mulMat.
 * Does arithmetic on matrices, with an operand supplied by said functions. */
void operandMats(char *args, Matrix *mats, char operand){
    int i = 0, j = 0, k;
    double val, scalar;
    Matrix *matFirstP, *matSecondP;
    char valString[MAX_LINE], addArgs[MAX_LINE], *scalarStr,
    *endOfString, *matFirst, *matSecond, *matResult, *extra;

    /* If trimmed args ends with comma, we throw. */
    if (args[strlen(args)-1] == ','){
        printf("Extraneous text after end of command\n");
        return;
    }

    /* If first matrix argument is not valid, we throw. */
    matFirst = strtok(args, ",");
    if (matFirst == NULL){
        printf("Missing argument\n");
        return;
    }
    matFirstP = getMat(mats, matFirst);
    if (matFirstP == NULL) /* getMat throws already. */
        return;

    if (operand == '+' || operand == '-' || operand == '*'){ /* In these commands, there is a second matrix arg. */
        /* If second matrix argument is not valid, we throw. */
        matSecond = strtok(NULL, ",");
        if (matSecond == NULL){
            printf("Missing argument\n");
            return;
        }
        matSecondP = getMat(mats, matSecond);
        if (matSecondP == NULL)
            return;
    } else if (operand == 'S'){
        /* In th command, there is scalar arg, if it is not valid, we throw. */
        scalarStr = strtok(NULL, ",");
        scalar = strtod(scalarStr, &endOfString);
        if (endOfString - scalarStr != strlen(scalarStr)){
            printf("Argument is not a scalar\n");
            return; /* Cancel this command, by returning without setting the matrix. */
        }
    }

    /* All commands have result matrix. If it is not valid, we throw. */
    matResult = strtok(NULL, ",");
    if (matResult == NULL){
        printf("Missing argument\n");
        return;
    }
    if (getMat(mats, matResult) == NULL) /* No need to fetch it, just check its valid. */
        return;

    /* If any more text exists in args, we throw exception as well. */
    extra = strtok(NULL, "");
    if (extra != NULL){
        printf("Extraneous text after end of command\n");
        return;
    }

    /* Prepare args for readMat in the end. */
    strcpy(addArgs, matResult);
    strcat(addArgs, ",");

    /* Iterate over columns and row of arg matrix\matrices. */
    while (i < MAT_DIM && j < MAT_DIM){
        /* Perform logic of commands, depending on operand supplied. */
        switch (operand) {
            case '+':
                /* Add matrices values. */
                val = matFirstP->arr[i][j] + matSecondP->arr[i][j];
                break;
            case '-':
                /* Subtract matrices values. */
                val = matFirstP->arr[i][j] - matSecondP->arr[i][j];
                break;
            case '*':
                /* Sum the multiplication of items on row i on matFirst, and column j on matSecond. */
                for (val = 0, k = 0; k < 4; k++){
                    val += matFirstP->arr[i][k] * matSecondP->arr[k][j];
                }
                break;
            case 'S':
                /* Multiply arg matrix values by arg scalar */
                val = matFirstP->arr[i][j] * scalar;
                break;
            case 'T':
                /* Transpose arg matrix values. */
                val = (i == j) ? matFirstP->arr[i][j] : matFirstP->arr[j][i];
                break;
            default:
                /* Throw, bad command. */
                printf("Error, bad command\n");
                return;
        }

        /* Prepare args for readMat. Insert all calculated values to args string. */
        sprintf(valString, "%7.2f", val);
        strcat(addArgs, valString);
        strcat(addArgs, ",");

        /* Control the iteration of matrix columns and rows. */
        if (++j == MAT_DIM){
            j = 0;
            i++;
        }
    }

    /* Now that args string is ready, we call our readMat function with args. */
    addArgs[strlen(addArgs)-1] = '\0';
    readMat(addArgs, mats);
}

/* addMats: adds all values of matrix1 and matrix2 and sets results into values of matrix3. */
void addMats(char *args, Matrix *mats){
    operandMats(args, mats, '+');
}

/* subtractMats: subtracts all values of matrix2 from matrix1 and sets results into values of matrix3. */
void subtractMats(char *args, Matrix *mats){
    operandMats(args, mats, '-');
}

/* multiplyMats: multiplies matrix1 by matrix2 and sets results into values of matrix3. */
void multiplyMats(char *args, Matrix *mats){
    operandMats(args, mats, '*');
}

/* multiplyMatByScalar: multiplies matrix1 by scalar value (double) and sets results into values of matrix2. */
void multiplyMatByScalar(char *args, Matrix *mats){
    operandMats(args, mats, 'S');
}

/* transposeMat: Transposes matrix1 and sets the new values into matrix2. */
void transposeMat(char *args, Matrix *mats){
    operandMats(args, mats, 'T');
}