#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "../include/types.h"
#include "../include/register.h"
#include "../include/menu.h"

bool login() {
    FILE * txt;
    CREDENTIALS credentials, credentialsToMatch;
    bool correctEmail = false, correctPassword = false;

    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        fflush(stdin);
        printf("Informe o email: ");
        scanf("%s", credentials.email);
        fflush(stdin);
        printf("Informe a senha: ");
        scanf("%s", credentials.password);

        while(fread(&credentialsToMatch, sizeof(CREDENTIALS), 1, txt) == 1) {
            if(strcmp(credentials.email, credentialsToMatch.email) == 0) {
                correctEmail = true;
                if(strcmp(credentials.password, credentialsToMatch.password) == 0) {
                    correctPassword = true;
                    break;
                }
            }
        }

        fclose(txt);
    }       

    if(correctEmail && correctPassword) {
        return true;
    }else {
        printf("Credenciais não correlacionam. Por favor, tente novamente. \n");
        return false;
    }
}

void signup() {
    CREDENTIALS credentials, credentialsToMatch;
    FILE * txt, * txtToMatch;
    bool alreadyExists = false;

    txt = fopen(ORIGINAL_FILENAME, "ab");
    txtToMatch = fopen(ORIGINAL_FILENAME, "rb");

    system("cls");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        fflush(stdin);
        printf("Email: ");
        scanf("%s", credentials.email);
        fflush(stdin);
        printf("Senha: ");
        scanf("%s", credentials.password);
        while(fread(&credentialsToMatch, sizeof(CREDENTIALS), 1, txtToMatch) == 1) {
            if(strcmp(credentials.email, credentialsToMatch.email) == 0) {
                alreadyExists = true;
                break;
            }
        }
        if(!alreadyExists) {
            fwrite(&credentials, sizeof(CREDENTIALS), 1, txt);
            fclose(txt);
            fclose(txtToMatch);
        }else {
            printf("Email já existente, tente outro. \n\n");
            fclose(txt);
            fclose(txtToMatch);
            signup();
        }
    }
}

int registerMenu() {
    strcpy(ORIGINAL_FILENAME, "./data/validation.txt");

    int option = 0;
    bool logged = false;
    system("cls");
    printf("*** Sistema de gerenciamento *** \n\n");
    printf("1 - Entrar \n");
    printf("2 - Registrar \n");
    printf("3 - Encerrar \n");
    scanf("%d", &option);
    switch(option) {
        case 1:
            system("cls");
            logged = login();
            if(!logged) {
                system("cls");
                printf("Credenciais não correlacionam. \n");
                printf("Pressione qualquer tecla para voltar ao menu. \n");
                getch();
            }else {
                system("cls");
                menu();
            }
            break;
        case 2:
            signup();
            break;
        case 3:
            break;
        default:
            printf("Opção inválida. \n");
            registerMenu();
            break;
    }

    return option;
}
