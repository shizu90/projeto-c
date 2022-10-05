#ifndef REQUESTS
#define REQUESTS

#include "./types.h"

void postRequest(REQUEST request, CLIENT client);
void updateRequest(REQUEST request, CLIENT client);
void deleteRequest(REQUEST request, CLIENT client);
void getRequest(REQUEST request);
void requestsMenu();

#endif