#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "../include/types.h"
#include "../include/register.h"
#include "../include/menu.h"
#include "../include/utils.h"

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
                    admin = credentialsToMatch.admin;
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
       if(getLines(txt, sizeof(CREDENTIALS)) == 0) {
        credentials.admin = true;
       }else credentials.admin = false;

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
            printf("Email já existente, tente outro. \n");
            fclose(txt);
            fclose(txtToMatch);
            getch();
        }
    }
}

void getCredentials(CREDENTIALS credentials) {
    FILE * txt;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        printf("Email | Senha | Admin \n\n");
        while(fread(&credentials, sizeof(CREDENTIALS), 1, txt) == 1) {
            printf("%s     ", credentials.email);
            printf("%s     ", credentials.password);
            if(credentials.admin) {
                printf("Sim\n");
            }else {
                printf("Não\n");
            }
        }

        fclose(txt);
    }
}

void deleteCredentials(CREDENTIALS credentials) {
    FILE * txt, * tmp;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL) {
        printf("Falha na abertura do arquivo. \n");
    }else {
        char email[250];
        tmp = fopen(TMP_FILENAME, "ab");
        printf("Digite o email para deletar: \n");
        scanf("%s", email);
        while(fread(&credentials, sizeof(CREDENTIALS), 1, txt) == 1) {
            if(strcmp(email, credentials.email) != 0) {
                fwrite(&credentials, sizeof(CREDENTIALS), 1, tmp);
            }else continue;
        }
        fclose(txt);
        fclose(tmp);
        remove(ORIGINAL_FILENAME);
        rename(TMP_FILENAME, ORIGINAL_FILENAME);

        printf("Usuário %s deletado. \n", email);
    }
}

void updateCredentials(CREDENTIALS credentials) {
    FILE * txt, * tmp;
    bool inEdit = false;
    int option;
    txt = fopen(ORIGINAL_FILENAME, "rb");
    if(txt == NULL) {
        printf("Falha na abertura de arquivo. \n");
    }else {
        char email[250];
        tmp = fopen(TMP_FILENAME, "ab");
        printf("Digite o email para editá-lo: ");
        scanf("%s", email);
        while(fread(&credentials, sizeof(CREDENTIALS), 1, txt) == 1) {
            if(strcmp(email, credentials.email) == 0) {
                inEdit = true;
                while(inEdit) {
                    system("cls");
                    printf("%s | %s |", credentials.email, credentials.password);
                    if(credentials.admin) {printf(" Sim\n\n");} else printf(" Não\n\n");
                    printf("Selecione o atributo para editar: \n");
                    printf("1 - Email\n");
                    printf("2 - Senha\n");
                    printf("3 - Admin\n");
                    printf("4 - Sair\n");
                    scanf("%d", &option);
                    switch(option) {
                        case 1:
                            system("cls");
                            printf("Email: ");
                            scanf("%s", credentials.email);
                            break;
                        case 2:
                            system("cls");
                            printf("Senha: ");
                            scanf("%s", credentials.password);
                            break;
                        case 3:
                            system("cls");
                            char admin;
                            printf("Admin (s/n): ");
                            getchar();
                            scanf("%c", &admin);
                            if(admin == 's') {credentials.admin = true;} else credentials.admin = false;
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
            fwrite(&credentials, sizeof(CREDENTIALS), 1, tmp);
        }
        fclose(txt);
        fclose(tmp);
        remove(ORIGINAL_FILENAME);
        rename(TMP_FILENAME, ORIGINAL_FILENAME);
    }
}

void credentialsMenu() {
    strcpy(ORIGINAL_FILENAME, "./data/validation.txt");
    strcpy(TMP_FILENAME, "./data/tmp_validation.txt");
    if(admin) {
        CREDENTIALS credentials;
        int option;
        bool inScreen = true;
        while(inScreen) {
            system("cls");
            printf("*** Gerenciamento de cadastro ***\n\n");
            printf("1 - Listar todos os cadastros\n");
            printf("2 - Editar cadastro\n");
            printf("3 - Deletar cadastro\n");
            printf("4 - Voltar\n");
            scanf("%d", &option);
            switch(option) {
                case 1:
                    system("cls");
                    getCredentials(credentials);
                    printf("\nPressione qualquer tecla para continuar: \n");
                    getch();
                    break;
                case 2:
                    system("cls");
                    updateCredentials(credentials);
                    printf("\nPressione qualquer tecla para continuar: \n");
                    getch();
                    break;
                case 3:
                    system("cls");
                    deleteCredentials(credentials);
                    printf("\nPressione qualquer tecla para continuar: \n");
                    getch();
                    break;
                case 4:
                    inScreen = false;
                    break;
                default:
                    printf("Opção inválida. \n");
                    break;
            }
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
