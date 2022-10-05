#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "../include/record.h"
#include "../include/types.h"

void generateRecord() {
    FILE * txt;
    FILE * txtEmployees, * txtRequests;
    EMPLOYEE employee;
    REQUEST request;
    time_t current = time(NULL);
    struct tm *gm_time = gmtime(&current);    
    float totalSalary = 0, totalRequestPrice = 0, difference = 0;
    char filename[70];
    snprintf(filename, 70, "./data/record_%d.txt", gm_time->tm_mon + 1);
    txt = fopen(filename, "w+");
    txtEmployees = fopen("./data/employees.txt", "rb");
    txtRequests = fopen("./data/requests.txt", "rb");
    if(txt == NULL || txtEmployees == NULL || txtRequests == NULL) {
        printf("Falha ao gerar arquivo, tente adicionar alguns pedidos e funcionários. \n");
    }else {
        while(fread(&employee, sizeof(EMPLOYEE), 1, txtEmployees) == 1) {
            totalSalary += employee.salary;
        }
        while(fread(&request, sizeof(REQUEST), 1, txtRequests) == 1) {
            if(request.ended.month == gm_time->tm_mon + 1) {
                totalRequestPrice += request.price;
            }
        }
        difference = totalRequestPrice - totalSalary;
        fprintf(txt, "---------------------------------------------\n");
        fprintf(txt, "               RELATÓRIO MENSAL\n");
        fprintf(txt, "---------------------------------------------\n\n");
        fprintf(txt, "           %s\n\n", ctime(&current));
        fprintf(txt, "Total dos salários: R$%.2f\n", totalSalary);
        fprintf(txt, "Total ganho com pedidos: R$%2.f\n", totalRequestPrice);
        fprintf(txt, "Diferença: R$%.2f\n\n", difference);
        if(difference < 0) {
            fprintf(txt, "Status: RUIM");
        }else {
            if(difference > totalSalary) {
                fprintf(txt, "Status: ÓTIMO");
            }else {
                fprintf(txt, "Status: BOM");
            }
        }
        fclose(txt);
        fclose(txtEmployees);
        fclose(txtRequests);

        printf("Relatório mensal gerado na pasta data. Nome do arquivo: %s\n", filename);
        printf("Pressione qualquer tecla para continuar: ");
        getch();
    }
}