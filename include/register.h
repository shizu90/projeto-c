#ifndef REGISTER
#define REGISTER

#include <stdbool.h>
#include "./types.h"

bool login();
void signup();
int registerMenu();

void getCredentials(CREDENTIALS credentials);
void deleteCredentials(CREDENTIALS credentials);
void updateCredentials(CREDENTIALS credentials);
void credentialsMenu();
#endif