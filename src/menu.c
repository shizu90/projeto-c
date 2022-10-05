#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/employees.h"
#include "../include/clients.h"
#include "../include/requests.h"
#include "../include/record.h"

void menu() {
    int option = 0;
    bool inMenu = true;
    while(inMenu) {
        system("cls");
        printf("O que deseja fazer? \n\n");
        printf("1 - Consultar funcionários \n");
        printf("2 - Consultar clientes \n");
        printf("3 - Consultar pedidos de clientes \n");
        printf("4 - Gerar relatório \n");
        printf("5 - Sair \n");
        scanf("%d", &option);
        switch(option) {
            case 1:
                system("cls");
                employeesMenu();
                break;
            case 2: 
                system("cls");
                clientsMenu();
                break;
            case 3:
                system("cls");
                requestsMenu(); 
                break;
            case 4:
                generateRecord();
                break;
            case 5:
                inMenu = false;
                break;
            default:
                system("cls");
                printf("Opção incorreta, digite novamente. \n");
                menu();
                break;
        }
    }
}