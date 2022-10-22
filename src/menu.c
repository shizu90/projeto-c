#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include "../include/menu.h"
#include "../include/employees.h"
#include "../include/clients.h"
#include "../include/requests.h"
#include "../include/record.h"
#include "../include/utils.h"
#include "../include/register.h"

void menu() {
    int option = 1, key = 0;
    bool inMenu = true;
    while(inMenu) {
        system(CLEAR);
        printf("--------------------\n");
        printf("***Seja bem-vindo***\n");
        printf("--------------------\n");
        printf(" O que deseja fazer?\n\n");
        arrowPointer(1, option);printf("1 - Consultar funcionários \n");
        arrowPointer(2, option);printf("2 - Consultar clientes \n");
        arrowPointer(3, option);printf("3 - Consultar pedidos de clientes \n");
        arrowPointer(4, option);printf("4 - Gerar relatório \n");
        if(admin) {
            arrowPointer(5, option);printf("5 - Gerenciar credenciais \n");
            arrowPointer(6, option);printf("6 - Sair \n");
        }else {
            arrowPointer(5, option);printf("5 - Sair \n");
        }
        key = getch();
        if(admin) {
            option = changeOption(key, option, 6, 1);
        }else {
            option = changeOption(key, option, 5, 1);
        }
        if(key == ENTER) {
            switch(option) {
                case 1:
                    system(CLEAR);
                    employeesMenu();
                    break;
                case 2: 
                    system(CLEAR);
                    clientsMenu();
                    break;
                case 3:
                    system(CLEAR);
                    requestsMenu(); 
                    break;
                case 4:
                    generateRecord();
                    break;
                case 5:
                    if(admin) {
                        system(CLEAR);
                        credentialsMenu();
                    }else {
                        inMenu = false;
                    }
                    break;
                case 6:
                    if(admin) inMenu = false;
                    break;
                default:
                    system(CLEAR);
                    printf("Opção incorreta, digite novamente. \n");
                    menu();
                    break;
            }
        }
    }
}