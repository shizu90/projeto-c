#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "../include/clients.h"
#include "../include/utils.h"

void postClient(CLIENT client) {
    FILE * txt;
    txt = fopen(ORIGINAL_FILENAME, "ab");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        int linesInFile = getLines(txt, sizeof(CLIENT));
        client.id = linesInFile + 1;
        linesInFile = client.id;
        client.requestCount = 0;
        printf("\n");
        fflush(stdin);
        printf("Digite o nome: ");
        gets(client.name);
        fflush(stdin);
        printf("Digite o cpf: ");
        gets(client.CPF);

        printf("<----Cliente adicionado com sucesso.---->\n");
        fwrite(&client, sizeof(CLIENT), 1, txt);
        fclose(txt);
    }
}

void updateClient(CLIENT client) {
    int id = 0, option = 1, lines = 0, key = 0;
    bool inEdit = false;
    FILE * txt, * tmp;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL || tmp == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        lines = getLines(txt, sizeof(CLIENT));
        printf("Digite o id do cliente para editá-lo: ");
        scanf("%d", &id);
        if(id - 1 <= lines) {
            tmp = fopen(TMP_FILENAME, "ab");
            while(fread(&client, sizeof(CLIENT), 1, txt) == 1) {
                if(id == client.id) {
                    inEdit = true;
                    while(inEdit) {
                        system(CLEAR);
                        printf("%d | %s | %s | %d \n\n", client.id, client.name, client.CPF, client.requestCount);
                        printf("Selecione o atributo para a edição: \n");
                        arrowPointer(1, option);printf("1 - Nome \n");
                        arrowPointer(2, option);printf("2 - Total de pedidos \n");
                        arrowPointer(3, option);printf("3 - CPF \n");
                        arrowPointer(4, option);printf("4 - Sair da edição \n");
                        key = getch();
                        option = changeOption(key, option, 4, 1);

                        if(key == ENTER) switch(option) {
                            case 1:
                                fflush(stdin);
                                printf("Nome: ");
                                gets(client.name);
                                break;
                            case 2:
                                printf("Total de pedidos: ");
                                scanf("%d", &client.requestCount);
                                break;
                            case 3:
                                fflush(stdin);
                                printf("CPF: ");
                                gets(client.CPF);
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
                fwrite(&client, sizeof(CLIENT), 1, tmp);
            }
            printf("<----Cliente atualizado com sucesso.---->\n");
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

void deleteClient(CLIENT client) {
    int id = 0, lines = 0;
    FILE * txt, * tmp;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    system(CLEAR);
    if(txt == NULL || tmp == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        lines = getLines(txt, sizeof(CLIENT));
        printf("Digite o id para a remoção: ");
        scanf("%d", &id);
        if(id - 1 <= lines) {
            tmp = fopen(TMP_FILENAME, "ab");
            while(fread(&client, sizeof(CLIENT), 1, txt) == 1) {
                if(id != client.id) {
                    if(client.id == id + 1) {
                        client.id = id;
                    }
                    fwrite(&client, sizeof(CLIENT), 1, tmp);
                }else {
                    continue;
                }
            }
            printf("<----Cliente deletado com sucesso.---->\n");
            fclose(txt);
            fclose(tmp);
            remove(ORIGINAL_FILENAME);
            rename(TMP_FILENAME, ORIGINAL_FILENAME);
        }else {
            printf("Id não existente. \n");
            fclose(txt);
        }
    }
}

void getClient(CLIENT client) {
    FILE * txt;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        printf("Id | Nome | CPF | Total de pedidos \n\n");
        while(fread(&client, sizeof(CLIENT), 1, txt) == 1) {
            printf("%d    ", client.id);
            printf("%s    ", client.name);
            printf("%s    ", client.CPF);
            printf("%d\n", client.requestCount);
        }
        fclose(txt);
    }
}

void clientsMenu() {
    strcpy(ORIGINAL_FILENAME, "./data/clients.txt");
    strcpy(TMP_FILENAME, "./data/tmp_clients.txt");

    CLIENT client;
    int option = 1;
    int key = 0;
    bool inScreen = true;
    while(inScreen) {
        system(CLEAR);
        printf("---------------------------------\n");
        printf("*** Gerenciamento de clientes ***\n");
        printf("---------------------------------\n\n");
        arrowPointer(1, option);printf("1 - Salvar cliente \n");
        arrowPointer(2, option);printf("2 - Editar cliente \n");
        arrowPointer(3, option);printf("3 - Remover cliente \n");
        arrowPointer(4, option);printf("4 - Listar clientes \n");
        arrowPointer(5, option);printf("5 - Voltar \n");
        key = getch();
        option = changeOption(key, option, 5, 1);

        if(key == ENTER) switch(option) {
            case 1:
                system(CLEAR);
                postClient(client);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 2:
                system(CLEAR);
                updateClient(client);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 3:
                system(CLEAR);
                deleteClient(client);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 4:
                system(CLEAR);
                getClient(client);
                printf("\nPression qualquer tecla para continuar: \n");
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