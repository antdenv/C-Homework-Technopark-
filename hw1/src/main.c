#include "Org_struct.h"
#include "Read_write.h"
#include <stdio.h>

int main() {
    organization** orgs = NULL;
    size_t count = 0;

    orgs = input_orgs("../files/test.txt", count);
    size_t orgs_size = get_size("../files/test.txt");
    
    if(orgs_size != 0) {
       send_data("../files/result.txt", orgs, orgs_size, "ISO");
    }

    free_orgs(orgs, orgs_size);

    return 0;
}