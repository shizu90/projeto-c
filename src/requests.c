#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "../include/requests.h"
#include "../include/utils.h"

void postRequest(REQUEST request, CLIENT client) {
    bool requestDelivered = false;
    FILE * txt, * txtClients, * tmpClients;
    txt = fopen(ORIGINAL_FILENAME, "ab");
    txtClients = fopen("./data/clients.txt", "rb");
    if(txt == NULL || txtClients == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        tmpClients = fopen("./data/tmp_clients.txt", "ab");
        int linesInFile = getLines(txt, sizeof(REQUEST));
        system("cls");
        request.id = linesInFile + 1;
        linesInFile = request.id;
        printf("\n");
        printf("Digite id do cliente: ");
        scanf("%d", &request.clientId);
        if(request.clientId - 1 <= getLines(txtClients, sizeof(CLIENT))) {
            while(fread(&client, sizeof(CLIENT), 1, txtClients) == 1) {
                if(request.clientId == client.id) {
                    client.requestCount += 1;
                    printf("Digite o total ganho/vai ganhar com o pedido: ");
                    scanf("%f", &request.price);
                    printf("Digite a data da inicialização do pedido: \n");
                    printf("Dia: ");
                    scanf("%d", &request.started.day);
                    printf("Mês: ");
                    scanf("%d", &request.started.month);
                    printf("Ano: ");
                    scanf("%d", &request.started.year);
                    printf("Pedido foi entregue? (s/n): ");
                    if(getch() == 's') {
                        printf("Digite a data de término do pedido: \n");
                        printf("Dia: ");
                        scanf("%d", &request.ended.day);
                        printf("Mês: ");
                        scanf("%d", &request.ended.month);
                        printf("Ano: ");
                        scanf("%d", &request.ended.year);
                    }else {
                        request.ended.day = 0;request.ended.month = 0;request.ended.year = 0;
                    }
                    fwrite(&request, sizeof(REQUEST), 1, txt);
                }
                fwrite(&client, sizeof(CLIENT), 1, tmpClients);
            }
        }else {
            printf("Cliente não está presente no sistema. \n");
        }
        fclose(tmpClients);
        fclose(txtClients);
        fclose(txt);
        remove("./data/clients.txt");
        rename("./data/tmp_clients.txt", "./data/clients.txt");
    }
}

void updateRequest(REQUEST request, CLIENT client) {
    int id = 0, option = 0, clientId = 0;
    bool inEdit = false;
    FILE * txt, * tmp, * txtClients, * tmpClients;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        int lines = getLines(txt, sizeof(REQUEST));
        printf("Digite o id para a edição: ");
        scanf("%d", &id);
        if(id - 1 <= lines) {
            tmp = fopen(TMP_FILENAME, "ab");
            while(fread(&request, sizeof(REQUEST), 1, txt) == 1) {
                if(id == request.id) {
                    inEdit = true;
                    while(inEdit) {
                        system("cls");
                        printf("%d | R$%2.f | %d/%d/%d | %d/%d/%d | %d \n\n", request.id, request.price, 
                        request.started.day, request.started.month, request.started.year, 
                        request.ended.day, request.ended.month, request.ended.year, request.clientId);
                        printf("Escolha o atributo para a edição: \n");
                        printf("1 - Preço \n");
                        printf("2 - Data de inicio \n");
                        printf("3 - Data de termino \n");
                        printf("4 - Id do cliente \n");
                        printf("5 - Sair da edição \n");
                        scanf("%d", &option);
                        switch(option) {
                            case 1:
                                system("cls");
                                printf("Preço: ");
                                scanf("%f", &request.price);
                                break;
                            case 2:
                                system("cls");
                                printf("Data de inicio: \n");
                                printf("Dia: \n");
                                scanf("%d", &request.started.day);
                                printf("Mês: ");
                                scanf("%d", &request.started.month);
                                printf("Ano: ");
                                scanf("%d", &request.started.year);
                                break;
                            case 3:
                                system("cls");
                                printf("Data de término: \n");
                                printf("Dia: \n");
                                scanf("%d", &request.ended.day);
                                printf("Mês: ");
                                scanf("%d", &request.ended.month);
                                printf("Ano: ");
                                scanf("%d", &request.ended.year);
                                break;
                            case 4:
                                system("cls");
                                txtClients = fopen("./data/clients.txt", "rb");
                                if(txtClients == NULL) {
                                    printf("Falha na abertura de arquivo. \n");
                                }else {
                                    printf("Id do cliente: ");
                                    scanf("%d", &clientId);
                                    if(clientId - 1 <= getLines(txtClients, sizeof(CLIENT))) {
                                        tmpClients = fopen("./data/tmp_clients.txt", "ab");
                                        while(fread(&client, sizeof(CLIENT), 1, txtClients) == 1) {
                                            if(clientId != client.id && request.clientId == client.id) {
                                                client.requestCount--;
                                            }else {
                                                if(clientId == client.id) client.requestCount++;
                                            }
                                            fwrite(&client, sizeof(CLIENT), 1, tmpClients);
                                        }
                                        request.clientId = clientId;
                                        fclose(txtClients);
                                        fclose(tmpClients);
                                        remove("./data/clients.txt");
                                        rename("./data/tmp_clients.txt", "./data/clients.txt");
                                    }else {
                                        fclose(txtClients);
                                        printf("Id não existente. \n");
                                    }
                                }
                                break;
                            case 5:
                                inEdit = false;
                                break;
                            default:
                                printf("Opção inválida. \n");
                                break;
                        }
                    }
                }
                fwrite(&request, sizeof(REQUEST), 1, tmp);
            }
            fclose(tmp);
            fclose(txt);
            remove(ORIGINAL_FILENAME);
            rename(TMP_FILENAME, ORIGINAL_FILENAME);
        }else {
            printf("Pedido não existente. \n");
        }
    }
}

void deleteRequest(REQUEST request, CLIENT client) {
    int id = 0, clientId = 0;
    FILE * txt, * tmp, * txtClients, * tmpClients;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    txtClients = fopen("./data/clients.txt", "rb");
    if(txt == NULL || txtClients == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        printf("Digite o id do pedido para a remoção: ");
        scanf("%d", &id);
        if(id - 1 <= getLines(txt, sizeof(REQUEST))) {
            tmp = fopen(TMP_FILENAME, "ab");
            tmpClients = fopen("./data/tmp_clients.txt", "ab");
            while(fread(&request, sizeof(REQUEST), 1, txt) == 1) {
                if(id != request.id) {
                    if(request.id == id + 1) {
                        request.id = id;
                    }
                    fwrite(&request, sizeof(REQUEST), 1, tmp);
                }else {
                    clientId = request.clientId;
                }
            }
            if(clientId > 0) {
                while(fread(&client, sizeof(CLIENT), 1, txtClients) == 1) {
                    if(clientId == client.id) {
                        client.requestCount--;
                    }
                    fwrite(&client, sizeof(CLIENT), 1, tmpClients);
                }
            }
            fclose(tmp);
            fclose(tmpClients);
            fclose(txt);
            fclose(txtClients);
            remove(ORIGINAL_FILENAME);
            rename(TMP_FILENAME, ORIGINAL_FILENAME);
            remove("./data/clients.txt");
            rename("./data/tmp_clients.txt", "./data/clients.txt");
        }else {
            printf("Pedido não existente. \n");
            fclose(txt);
            fclose(txtClients);
        }
    }
}

void getRequest(REQUEST request) {
    FILE * txt;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        printf("Id | Preço | Data de inicio | Data de término | Id do cliente \n\n");
        while(fread(&request, sizeof(REQUEST), 1, txt) == 1) {
            printf("%d  ", request.id);
            printf("R$%2.f  ", request.price);
            printf("%d/%d/%d  ", request.started.day, request.started.month, request.started.year);
            if(request.ended.month == 0) {
                printf("Em andamento  ");
            }else printf("%d/%d/%d  ", request.ended.day, request.ended.month, request.ended.year);
            printf("%d  \n", request.clientId);
        }
        fclose(txt);
    }
}

void requestsMenu() {
    strcpy(ORIGINAL_FILENAME, "./data/requests.txt");
    strcpy(TMP_FILENAME, "./data/tmp_requests.txt");

    REQUEST request;
    CLIENT client;
    int option = 0;
    bool inScreen = true;
    while(inScreen) {
        system("cls");
        printf("*** Gerenciamento de pedidos ***\n\n");
        printf("1 - Salvar pedido \n");
        printf("2 - Editar pedido \n");
        printf("3 - Remover pedido \n");
        printf("4 - Listar pedidos \n");
        printf("5 - Voltar \n");
        scanf("%d", &option);
        switch(option) {
            case 1:
                system("cls");
                postRequest(request, client);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 2:
                system("cls");
                updateRequest(request, client);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 3:
                system("cls");
                deleteRequest(request, client);
                printf("\nPressione qualquer tecla para continuar: \n");
                getch();
                break;
            case 4:
                system("cls");
                getRequest(request);
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