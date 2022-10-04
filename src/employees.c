#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/employees.h"
#include "../include/utils.h"

struct employee {
    int id;
    char name[60];
    float salary;
    char department[60];
};

char x;

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
        scanf("%s", employee.name);
        fflush(stdin);
        printf("Digite o salário: ");
        scanf("%f", &employee.salary);
        fflush(stdin);
        printf("Digite o departamento: ");
        scanf("%s", employee.department);

        fwrite(&employee, sizeof(EMPLOYEE), 1, txt);
    }
    fclose(txt);
}

void editEmployee(EMPLOYEE employee) {
    int id = 0, option = 0, lines = 0;
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
                        system("clear");
                        printf("%d | %s | R$%.2f | %s \n\n", employee.id, employee.name, employee.salary, employee.department);
                        printf("Selecione o atributo para a edição: \n");
                        printf("1 - Nome \n");
                        printf("2 - Salário \n");
                        printf("3 - Departamento \n");
                        printf("4 - Sair da edição \n");
                        scanf("%d", &option);
                        switch(option) {
                            case 1:
                                fflush(stdin);
                                printf("Nome: ");
                                scanf("%s", employee.name);
                                break;
                            case 2:
                                printf("Salário: ");
                                scanf("%f", &employee.salary);
                                break;
                            case 3:
                                fflush(stdin);
                                printf("Departamento: ");
                                scanf("%s", employee.department);
                                break;
                            case 4:
                                inEdit = false;
                                break;
                            default:
                                printf("Opção inválida. \n");
                                break;
                        }
                    }
                    fwrite(&employee, sizeof(EMPLOYEE), 1, tmp);
                }else {
                    fwrite(&employee, sizeof(EMPLOYEE), 1, tmp);
                }
            }
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
    system("clear");
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
                    fwrite(&employee, sizeof(EMPLOYEE),1 , tmp);
                }else {
                    continue;
                }
            }
            fclose(tmp);
            remove(ORIGINAL_FILENAME);
            rename(TMP_FILENAME, ORIGINAL_FILENAME);
        }else {
            printf("Id não existente. \n");
        }
        fclose(txt);
    }
}

void getEmployee(EMPLOYEE employee) {
    FILE * txt;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        system("clear");
        printf("Id | Nome | Salário | Departamento \n\n");
        while(fread(&employee, sizeof(EMPLOYEE), 1, txt) == 1) {
            printf("%d  ", employee.id);
            printf("%s  ", employee.name);
            printf("R$%.2f  ", employee.salary);
            printf("%s  \n", employee.department);
        }
        fclose(txt);
    }
}

void employeesMenu() {
    strcpy(ORIGINAL_FILENAME, "employees.txt");
    strcpy(TMP_FILENAME, "tmp_employees.txt");

    EMPLOYEE employee;
    int option = 0;
    bool inScreen = true;
    while(inScreen) {
        system("clear");
        printf("*** Gerenciamento de funcionários ***\n\n");
        printf("1 - Salvar funcionário \n");
        printf("2 - Editar funcionário \n");
        printf("3 - Remover funcionário \n");
        printf("4 - Listar funcionários \n");
        printf("5 - Voltar \n");
        scanf("%d", &option);
        switch(option) {
            case 1:
                system("clear");
                postEmployee(employee);
                printf("\nPressione qualquer tecla para continuar: \n");
                scanf(" %c", &x);
                break;
            case 2:
                system("clear");
                editEmployee(employee);
                printf("\nPressione qualquer tecla para continuar: \n");
                scanf(" %c", &x);
                break;
            case 3:
                system("clear");
                deleteEmployee(employee);
                printf("\nPressione qualquer tecla para continuar: \n");
                scanf(" %c", &x);
                break;
            case 4:
                getEmployee(employee);
                printf("\nPressione qualquer tecla para continuar: \n");
                scanf(" %c", &x);
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

