#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include "./include/register.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    int option = 0;
    while(option != 3) {
        option = registerMenu();
    }
    system("clear");
    return 0;
}