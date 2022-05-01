#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_LENGTH 45 /* this is just an average line length from google search */

char c;
int sumChars, sumAlphaNum;

void printLines(char *);