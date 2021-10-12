#pragma once

#include "Org_struct.h"
#include <stdio.h>

#define SUCCESS 0
#define NULL_PTR 1
#define MEMORY_ERROR 2
#define READ_ERROR 3
#define FAIL_ERROR 4

size_t get_size(const char* filename);
organization* input_organization(FILE* file);
organization** input_orgs(const char* filename, size_t size);
int output_organization(const char* filename, const organization* org);
