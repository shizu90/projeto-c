#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/employees.h"

void menu() {
    int option = 0;
    bool inScreen = true;
    printf("O que deseja fazer? \n\n");
    printf("1 - Consultar funcionários \n");
    printf("2 - Consultar clientes \n");
    printf("3 - Consultar pedidos de clientes \n");
    printf("4 - Gerar relatório \n");
    printf("5 - Sair \n");
    scanf("%d", &option);
    switch(option) {
        case 1:
        system("clear");
            employeesMenu();
            break;
        case 2: 
            break;
        case 3: 
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            system("clear");
            printf("Opção incorreta, digite novamente. \n");
            menu();
            break;
    }
}