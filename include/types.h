#ifndef TYPES
#define TYPES

extern char * ORIGINAL_FILENAME;
extern char * TMP_FILENAME;

typedef struct credentials CREDENTIALS;
typedef struct employee EMPLOYEE;
typedef struct client CLIENT;
typedef struct date DATE;
typedef struct request REQUEST;

struct date {
    int day;
    int month;
    int year;
};

struct client {
    int id;
    char name[60];
    int requestCount;
};


struct request {
    int id;
    int clientId;
    char title[100];
    float price;
    DATE started;
    DATE ended;
};

struct employee {
    int id;
    char name[60];
    float salary;
    char department[60];
};

struct credentials {
    char email[250];
    char password[15];
};

#endif