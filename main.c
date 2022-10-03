#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    printf("Hello world.");
    return 0;
}