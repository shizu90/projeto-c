#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
#include "./include/register.h"
#include "./include/types.h"
#include "./include/utils.h"

char * ORIGINAL_FILENAME;
char * TMP_FILENAME;

int main() {
    ORIGINAL_FILENAME = malloc(50);
    TMP_FILENAME = malloc(50);
    DIR * data = opendir("data");
    if(!data) {
        system("mkdir data");
    }else {
        closedir(data);
    }

    setlocale(LC_ALL, "Portuguese-Brasil");
    system("chcp 65001");
    int option = 0;
    while(option != 3) {
        option = registerMenu();
    }
    free(ORIGINAL_FILENAME);
    free(TMP_FILENAME);
    system(CLEAR);
    return 0;
}