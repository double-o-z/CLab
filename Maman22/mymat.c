#include "mymat.h"

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
    if (matP - mats > 5) {
        printf("Undefined matrix name\n");
        return NULL;
    }
    return matP;
}

/* printMax: prints a matrix to console.
 * Gets argument matrix pointer */
void printMat(char *matName, Matrix *mats){
    int i, j;
    Matrix *matP = getMat(mats, matName);
    if (matP == NULL)
        return;
    printf("\n\t\t**** %s ****\n", matP->name);
    for (i = 0; i < 4; ++i) {
        putchar('\t');
        for (j = 0; j < 4; ++j){
            printf("%7.2f\t", matP->arr[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

/* readMat: sets values to a given matrix.
 * Gets arguments: MATRIX_NAME,VAL1,VAL2,...
 * (sets between 0 to 16 values, by order of input). */
void readMat(char *args, Matrix *mats){
    int i = 0, j = 0, argsCount = 0;
    char *valString, *endOfString;
    double val;
    double arr[4][4] = {0};
    char *matName;
    char last;
    int foundArg = 0;
    Matrix *matP;
    last = args[strlen(args)-1];
    matName = strtok(args, ",");
    matP = getMat(mats, matName);
    if (matP == NULL)
        return;

    if (!isalnum(last)){ /* If last char of args is not alphanumeric (after white space trim!), we cancel command. */
        printf("Extraneous text after end of command\n");
        return;
    }
    while (argsCount++ < 16){
        val = 0.0;
        if ((valString = strtok(NULL, ",")) != NULL) {
            if (!foundArg)
                foundArg = 1;
            val = strtod(valString, &endOfString);
            /*printf("val: %.2f\n", val);*/
            if (endOfString - valString != strlen(valString)){
                printf("Argument is not a real number\n");
                return; /* Cancel this command, by returning without setting the matrix. */
            }
        } else {
            if (!foundArg){  /* If we got here, it means 'strtok' returned NULL on the first time, so we cancel. */
                printf("Missing argument\n");
                return;
            }
        }
        arr[i][j++] = val;
        if (j == MAT_DIM){
            j = 0;
            i++;
        }
    }
    /* Only if all arguments are valid doubles, we insert into the matrix. */
    /* If even one of the arguments is invalid, the function would return without changing the matrix. */
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j)
            matP->arr[i][j] = arr[i][j];
    }
}

/* operandMats: utility function that serves functions: addMat, subMat, mulMat.
 * Does arithmetic on matrices, with an operand supplied by said functions. */
void operandMats(char *args, Matrix *mats, char operand){
    int i = 0, j = 0, k;
    double val, scalar;
    char valString[MAX_LINE];
    char addArgs[MAX_LINE];
    char *scalarStr, *endOfString;
    Matrix *matFirstP, *matSecondP;
    char *matFirst;
    char *matSecond;
    char *matResult;
    char *extra;

    if (args[strlen(args)-1] == ','){
        printf("Extraneous text after end of command\n");
        return;
    }

    matFirst = strtok(args, ",");
    if (matFirst == NULL){
        printf("Missing argument\n");
        return;
    }
    matFirstP = getMat(mats, matFirst);
    if (matFirstP == NULL)
        return;
    if (operand == '+' || operand == '-' || operand == '*'){
        matSecond = strtok(NULL, ",");
        if (matSecond == NULL){
            printf("Missing argument\n");
            return;
        }
        matSecondP = getMat(mats, matSecond);
        if (matSecondP == NULL)
            return;
    } else if (operand == 'S'){
        scalarStr = strtok(NULL, ",");
        scalar = strtod(scalarStr, &endOfString);
        if (endOfString - scalarStr != strlen(scalarStr)){
            printf("Argument is not a scalar\n");
            return; /* Cancel this command, by returning without setting the matrix. */
        }
    }
    matResult = strtok(NULL, ",");
    if (matResult == NULL){
        printf("Missing argument\n");
        return;
    }
    if (getMat(mats, matResult) == NULL) /* Checking that result mat is a valid matrix name. */
        return;

    /* If any more text exists in args, we throw exception as well. */
    extra = strtok(NULL, "");
    if (extra != NULL){
        printf("Extraneous text after end of command\n");
        return;
    }

    strcpy(addArgs, matResult);
    strcat(addArgs, ",");

    while (i < MAT_DIM && j < MAT_DIM){
        switch (operand) {
            case '+':
                val = matFirstP->arr[i][j] + matSecondP->arr[i][j];
                break;
            case '-':
                val = matFirstP->arr[i][j] - matSecondP->arr[i][j];
                break;
            case '*':
                /* Sum the multiplication of items on row i on matFirst, and column j on matSecond. */
                for (val = 0, k = 0; k < 4; k++){
                    val += matFirstP->arr[i][k] * matSecondP->arr[k][j];
                }
                break;
            case 'S':
                val = matFirstP->arr[i][j] * scalar;
                break;
            case 'T':
                val = (i == j) ? matFirstP->arr[i][j] : matFirstP->arr[j][i];
                break;
            default:
                printf("Error, bad command\n");
                return;
        }
        sprintf(valString, "%7.2f", val);
        strcat(addArgs, valString);
        strcat(addArgs, ",");
        if (++j == MAT_DIM){
            j = 0;
            i++;
        }
    }
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