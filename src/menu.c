#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/employees.h"
#include "../include/clients.h"
#include "../include/requests.h"
#include "../include/record.h"
#include "../include/utils.h"
#include "../include/register.h"

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
        if(admin) {
            printf("5 - Gerenciar credenciais \n");
            printf("6 - Sair \n");
        }else {
            printf("5 - Sair \n");
        }
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
                if(admin) {
                    system("cls");
                    credentialsMenu();
                }else {
                    inMenu = false;
                }
                break;
            case 6:
                if(admin) inMenu = false;
                break;
            default:
                system("cls");
                printf("Opção incorreta, digite novamente. \n");
                menu();
                break;
        }
    }
}