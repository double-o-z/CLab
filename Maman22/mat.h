#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE 1000

struct matObj {
    float arr[4][4];
    char *name;
    void (*func)();
};

char *trimString(char *s);
void initMats(struct matObj mats[]);
void readMat(char *args);
void printMat(char *mat, struct matObj *mats);
void processCommand(struct matObj mats[], char *command, char *args);