#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include "./include/register.h"
#include "./include/types.h"

char * ORIGINAL_FILENAME;
char * TMP_FILENAME;

int main() {
    ORIGINAL_FILENAME = malloc(50);
    TMP_FILENAME = malloc(50);

    setlocale(LC_ALL, "Portuguese-Brasil");
    system("chcp 65001");
    int option = 0;
    while(option != 3) {
        option = registerMenu();
    }
    system("cls");
    return 0;
}