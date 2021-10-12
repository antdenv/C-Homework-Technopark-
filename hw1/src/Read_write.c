#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Read_write.h"

size_t get_size(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) return 0;

    size_t size = 0;
    while (!feof(file)) {
        fscanf(file, "%*[^\n]%*c");
        size++;
    }

    return size;
}

organization* input_organization(FILE* file) {
    if (file == NULL) return NULL;

    char name[6];
    char type[50];
    char full_name[50];
    int rus = 0;
    int a_date[3];
    int w_date[3];

    fscanf(file, "%5s", name);
    fscanf(file, "%29s", type);
    fscanf(file, "%49s", full_name);
    fscanf(file, "%d", &rus);

    fscanf(file, "%2d", &a_date[0]);
    fscanf(file, "%2d", &a_date[1]);
    fscanf(file, "%4d", &a_date[2]);

    date *date_a = (date*)malloc(sizeof(date));
    date_a->day = a_date[0];
    date_a->month = a_date[1];
    date_a->year = a_date[2];

    fscanf(file, "%2d", &w_date[0]);
    fscanf(file, "%2d", &w_date[1]);
    fscanf(file, "%4d", &w_date[2]);

    date *date_w = (date*)malloc(sizeof(date));
    date_w->day = w_date[0];
    date_w->month = w_date[1];
    date_w->year = w_date[2];

    organization* org = (organization*)malloc(sizeof(organization));
    org = create_organization(name, type, full_name, rus, date_a, date_w);
    if (org == NULL) return NULL;

    free(date_a);
    free(date_w);

    return org;
}

organization** input_orgs(const char* filename, size_t size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return NULL;

    size = get_size(filename);

    organization** orgs;
    orgs = create_orgs(size);
    if (orgs == NULL) {
        return NULL;
    }

    int error = 0;
    for (size_t i = 0; i < size; ++i) {
        orgs[i] = input_organization(file);
    }

    if (error) {
        free_orgs(orgs, size);
        orgs = NULL;
    }

    fclose(file);
    return orgs;
}

int output_organization(const char* filename, const organization* org) {
    FILE* file = fopen(filename, "w");
    if (file == NULL || org == NULL) return NULL_PTR;

    fprintf(file, "%s ", org->name);
    fprintf(file, "%s ", org->type);
    fprintf(file, "%s ", org->full_name);
    fprintf(file, "%d ", org->rus);

    fprintf(file, "%d/", org->date_accept->day);
    fprintf(file, "%d/", org->date_accept->month);
    fprintf(file, "%d ", org->date_accept->year);

    fprintf(file, "%d/", org->date_work->day);
    fprintf(file, "%d/", org->date_work->month);
    fprintf(file, "%d\n", org->date_work->year);

    fclose(file);
    return SUCCESS;
}