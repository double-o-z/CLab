#include "mat.h"

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
        keep = p = s;
        while (*p){
            if (isspace((unsigned char) *p)){
                if (firstSpace == 1){
                    *p = ' '; /* replace tab with white space for comfort. */
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

/* getMat: returns a pointer to given matrix name. */
Matrix *getMat(Matrix *mats, char *matName){
    int i;
    Matrix *matP = mats;
    for (i =0; i < 6; i++, matP++)  /* Get correct matrix */
        if (strcmp(matP->name, matName) == 0)
            break;
    return matP;
}

/* printMax: prints a matrix to console.
 * Gets argument matrix pointer */
void printMat(char *matName, Matrix *mats){
    int i, j;
    Matrix *matP = getMat(mats, matName);
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
    char *valString;
    double val;
    char *matName;
    Matrix *matP;
    matName = strtok(args, ",");
    matP = getMat(mats, matName);
    while (argsCount++ < 16){
        val = 0.0;
        if ((valString = strtok(NULL, ",")) != NULL)
            val = strtod(valString, NULL);
        matP->arr[i][j++] = val;
        if (j == MAT_DIM){
            j = 0;
            i++;
        }
    }
}

/* operandMats: utility function that serves functions: addMat, subMat, mulMat.
 * Does arithmetic on matrices, with an operand supplied by said functions. */
void operandMats(char *args, Matrix *mats, char operand){
    int i = 0, j = 0;
    double val, scalar;
    char valString[MAX_LINE];
    char addArgs[MAX_LINE];
    char *scalarStr;
    Matrix *matFirstP, *matSecondP;
    char *matFirst;
    char *matSecond;
    char *matResult;

    matFirst = strtok(args, ",");
    matFirstP = getMat(mats, matFirst);
    if (operand == '+' || operand == '-' || operand == '*'){
        matSecond = strtok(NULL, ",");
        matSecondP = getMat(mats, matSecond);
    } else if (operand == 'S'){
        scalarStr = strtok(NULL, ",");
        scalar = strtod(scalarStr, NULL);
    }
    matResult = strtok(NULL, ",");
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
                val = matFirstP->arr[i][j] * matSecondP->arr[i][j];
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