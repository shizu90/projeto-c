#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdbool.h>
#include "./types.h"

#define ARROW_DOWN 80
#define ARROW_UP 72
#define ENTER 13

extern bool admin;
static const char CLEAR[] = "cls";
int getLines(FILE * txt, int sizeOfData);
void getDate(DATE * date);
void arrowPointer(int currentPosition, int arrowPosition);
int changeOption(int key, int option, int max, int min);

#endif