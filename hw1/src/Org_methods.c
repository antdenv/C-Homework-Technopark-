#include "Org_struct.h"
#include "Read_write.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

date* init_date() {
    date* data = (date*)malloc(sizeof(date));

    if (data == NULL) return NULL;

    data->day = 0;
    data->month = 0;
    data->year = 0;

    return data;
}

date* create_date(const int n_day, const int n_month, const int n_year) {
    date* data = init_date();
    if (data == NULL) return NULL;

    data->day = n_day; 
    data->month = n_month; 
    data->year = n_year;

    return data;
}

organization* init_organization() {
    organization* org = (organization*)malloc(sizeof(organization));
    org->date_accept = init_date();
    org->date_work = init_date();

    if (org == NULL || org->date_accept == NULL || org->date_work == NULL) {
        return NULL;
    }

    org->name = NULL;
    org->type = NULL;
    org->full_name = NULL;
    org->rus = 0;

    return org;
}

organization* create_organization(const char* name, const char* type, const char* full_name, const int ru, const date* date_a, const date* date_w) {
    organization* org = init_organization();
    if (org == NULL) return NULL;

    char* pname = calloc(strlen(name) + 1, sizeof(char));
    if (pname == NULL || strncpy(pname, name, strlen(name) + 1) == NULL) {
        free(pname);
        return NULL;
    }

    char* ptype = calloc(strlen(type) + 1, sizeof(char));
    if (ptype == NULL || strncpy(ptype, type, strlen(type) + 1) == NULL) {
        free(ptype);
        free(pname);
        return NULL;
    }

    char* fname = calloc(strlen(full_name) + 1, sizeof(char));
    if (fname == NULL || strncpy(fname, full_name, strlen(full_name) + 1) == NULL) {
        free(fname);
        free(ptype);
        free(pname);
        return NULL;
    }

    org->name = pname;
    org->type = ptype;
    org->full_name = fname;

    org->rus = ru;

    org->date_accept->day = date_a->day;
    org->date_accept->month = date_a->month;
    org->date_accept->year = date_a->year;

    org->date_work->day = date_w->day;
    org->date_work->month = date_w->month;
    org->date_work->year = date_w->year;

    return org;
}

organization** create_orgs(size_t size) {
    if (size == 0) {
        return NULL;
    }

    organization** orgs = calloc(size, sizeof(organization));

    return orgs;
}

date** create_dates(size_t size) {
    if (size == 0) return NULL;

    date** dates = calloc(size, sizeof(date));

    return dates;
}

void free_organization(organization* organization) {
    if (organization == NULL) return;

    free(organization->name);
    free(organization->type);
    free(organization->full_name);
    
    free(organization->date_accept);
    free(organization->date_work);

    free(organization);
}

void free_orgs(organization** orgs, size_t size) {
    if (orgs == NULL) return;

    for (size_t i = 0; i < size; ++i) free_organization(orgs[i]);

    free(orgs);
}

int send_data(const char* filename, organization** orgs, size_t size, const char* name) {
    FILE* file = fopen(filename, "w");
    if (orgs == NULL || file == NULL) return NULL_PTR;

    for (size_t i = 0; i < size; ++i) {
        if (strcmp(name, orgs[i]->name) == 0) {
            int res = output_organization(filename, orgs[i]);
            if (res) return FAIL_ERROR;
        }
    }

    return SUCCESS;
}