#pragma once 

#include <stddef.h>

#define SUCCESS 0
#define NULL_PTR 1
#define MEMORY_ERROR 2
#define READ_ERROR 3
#define FAIL_ERROR 4

struct Date {
    int day;
    int month;
    int year;
};

typedef struct Date date;

struct Organization {
    char* name;
    char* type;
    char* full_name;
    int rus;
    date* date_accept;
    date* date_work;
};

typedef struct Organization organization;

date* init_date();
date* create_date(const int n_day, const int n_month, const int n_year);
organization* init_organization();
organization* create_organization(const char* name, const char* type, const char* full_name, const int ru, const date* date_a, const date* date_w);
organization** create_orgs(size_t size);
date** create_dates(size_t size);
void free_organization(organization* organization);
void free_orgs(organization** orgs, size_t size);

int send_data(const char* filename, organization** orgs, size_t size, const char* name);


