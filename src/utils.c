#include <stdbool.h>
#include <time.h>
#include "../include/utils.h"
#include "../include/types.h"

bool admin = false;

int getLines(FILE * txt, int sizeOfData) {
    int fileSize, linesInFile;
    fseek(txt, 0L, SEEK_END);
    fileSize = ftell(txt);
    linesInFile = fileSize / sizeOfData;
    rewind(txt);
    return linesInFile;
}

void getDate(DATE *date) {
    time_t current = time(NULL);
    struct tm *gm_time = gmtime(&current); 
    printf("Dia: ");
    scanf("%d", &date->day);
    if(date->day > 0 && date->day <= 31) {
        printf("Mês: ");
        scanf("%d", &date->month);
        if(date->month > 0 && date->month <= 12) {
            printf("Ano: ");
            scanf("%d", &date->year);
            if(!(date->year > 1900 && date->year <= (gm_time->tm_year + 1900))) {
                getDate(date);
            }
        }else {
            printf("Mês inválido.\n");
            getDate(date);
        }
    }else {
        printf("Dia inválido.\n");
        getDate(date);
    }
}

void arrowPointer(int currentPosition, int arrowPosition) {
    if(currentPosition == arrowPosition) {
        printf(" >> ");
    }else {
        printf("    ");
    }
}

int changeOption(int key, int option, int max, int min) {
    if(key == ARROW_DOWN) {
        if(option == max) {
            return min;
        }else {
            return option+=1;
        }
    }else if(key == ARROW_UP) {
        if(option == min) {
            return max;
        }else {
            return option-=1;
        }
    }else return option;
}