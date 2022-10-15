#include <stdbool.h>
#include "../include/utils.h"

bool admin = false;

int getLines(FILE * txt, int sizeOfData) {
    int fileSize, linesInFile;
    fseek(txt, 0L, SEEK_END);
    fileSize = ftell(txt);
    linesInFile = fileSize / sizeOfData;
    rewind(txt);
    return linesInFile;
}