#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "../include/employees.h"
#include "../include/utils.h"

void postEmployee(EMPLOYEE employee) {
    FILE * txt;
    txt = fopen(ORIGINAL_FILENAME, "ab");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo.");
    }else {
        int linesInFile = getLines(txt, sizeof(EMPLOYEE));
        employee.id = linesInFile + 1;
        linesInFile = employee.id;
        printf("\n");
        fflush(stdin);
        printf("Digite o nome: ");
        gets(employee.name);
        fflush(stdin);
        printf("Digite o salário: ");
        scanf("%f", &employee.salary);
        fflush(stdin);
        printf("Digite o departamento: ");
        gets(employee.department);

        fwrite(&employee, sizeof(EMPLOYEE), 1, txt);
        printf("<----Funcionário adicionado com sucesso.---->");
        fclose(txt);
    }
}

void updateEmployee(EMPLOYEE employee) {
    int id = 0, option = 1, lines = 0, key = 0;
    bool inEdit = false;
    FILE * txt, * tmp;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL || tmp == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        lines = getLines(txt, sizeof(EMPLOYEE));
        printf("Digite o id do funcionário para editá-lo: ");
        scanf("%d", &id);
        if(id - 1 <= lines) {
            tmp = fopen(TMP_FILENAME, "ab");
            while(fread(&employee, sizeof(EMPLOYEE), 1, txt) == 1) {
                if(id == employee.id) {
                    inEdit = true;
                    while(inEdit) {
                        system(CLEAR);
                        printf("%d | %s | R$%.2f | %s \n\n", employee.id, employee.name, employee.salary, employee.department);
                        printf("Selecione o atributo para a edição: \n");
                        arrowPointer(1, option);printf("1 - Nome \n");
                        arrowPointer(2, option);printf("2 - Salário \n");
                        arrowPointer(3, option);printf("3 - Departamento \n");
                        arrowPointer(4, option);printf("4 - Sair da edição \n");
                        key = getch();
                        option = changeOption(key, option, 4, 1);
                        if(key == ENTER) switch(option) {
                            case 1:
                                fflush(stdin);
                                printf("Nome: ");
                                gets(employee.name);
                                break;
                            case 2:
                                printf("Salário: ");
                                scanf("%f", &employee.salary);
                                break;
                            case 3:
                                fflush(stdin);
                                printf("Departamento: ");
                                gets(employee.department);
                                break;
                            case 4:
                                inEdit = false;
                                break;
                            default:
                                printf("Opção inválida. \n");
                                break;
                        }
                    }
                }
                fwrite(&employee, sizeof(EMPLOYEE), 1, tmp);
            }
            printf("<----Funcionário atualizado com sucesso.---->\n");
            fclose(tmp);
            fclose(txt);
            remove(ORIGINAL_FILENAME);
            rename(TMP_FILENAME, ORIGINAL_FILENAME);
        }else {
            printf("Id não existente. \n");
            fclose(txt);
        }
    }
}

void deleteEmployee(EMPLOYEE employee) {
    int id = 0, lines = 0;
    FILE * txt, * tmp;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    system(CLEAR);
    if(txt == NULL || tmp == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        lines = getLines(txt, sizeof(EMPLOYEE));
        printf("Digite o id para a remoção: ");
        scanf("%d", &id);
        if(id - 1 <= lines) {
            tmp = fopen(TMP_FILENAME, "ab");
            while(fread(&employee, sizeof(EMPLOYEE), 1, txt) == 1) {
                if(id != employee.id) {
                    if(employee.id == id + 1) {
                        employee.id = id;
                    }
                    fwrite(&employee, sizeof(EMPLOYEE), 1, tmp);
                }else {
                    continue;
                }
            }
            printf("<----Funcionário deletado com sucesso.---->\n");
            fclose(tmp);
            fclose(txt);
            remove(ORIGINAL_FILENAME);
            rename(TMP_FILENAME, ORIGINAL_FILENAME);
        }else {
            printf("Id não existente. \n");
            fclose(txt);
        }
    }
}

void getEmployee(EMPLOYEE employee) {
    FILE * txt;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        printf("Id | Nome | Salário | Departamento \n\n");
        while(fread(&employee, sizeof(EMPLOYEE), 1, txt) == 1) {
            printf("%d    ", employee.id);
            printf("%s    ", employee.name);
            printf("R$%.2f    ", employee.salary);
            printf("%s\n", employee.department);
        }
        fclose(txt);
    }
}

void employeesMenu() {
    strcpy(ORIGINAL_FILENAME, "./data/employees.txt");
    strcpy(TMP_FILENAME, "./data/tmp_employees.txt");

    EMPLOYEE employee;
    int option = 1, key = 0;
    bool inScreen = true;
    while(inScreen) {
        system(CLEAR);
        printf("-------------------------------------\n");
        printf("*** Gerenciamento de funcionários ***\n");
        printf("-------------------------------------\n\n");
        arrowPointer(1, option);printf("1 - Salvar funcionário \n");
        arrowPointer(2, option);printf("2 - Editar funcionário \n");
        arrowPointer(3, option);printf("3 - Remover funcionário \n");
        arrowPointer(4, option);printf("4 - Listar funcionários \n");
        arrowPointer(5, option);printf("5 - Voltar \n");
        key = getch();
        option = changeOption(key, option, 5, 1);

        if(key == ENTER) switch(option) {
            case 1:
                system(CLEAR);
                postEmployee(employee);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 2:
                system(CLEAR);
                updateEmployee(employee);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 3:
                system(CLEAR);
                deleteEmployee(employee);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 4:
                system(CLEAR);
                getEmployee(employee);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 5:
                inScreen = false;
                break;
            default:
                printf("Opção inválida. \n");
                break;
        }
    }
}

