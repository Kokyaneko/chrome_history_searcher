#include <stdio.h>
#include <string.h>
#include "struct.h"

#define MAX_HISTORY_NUMBER 10000
#define MAX_DOMAINS 3000
#define DOMAIN_LEN 256

int count_d(const char* url,const int data_number){
    if (url == NULL || strlen(url) == 0) return 2;

    for(int i=0;i<data_number;i++){
        if(strstr(dbs[i]->url,"file://") != NULL)continue;//ignore "file://"

        const char *start = strstr(dbs[i]->url,"://");
        if(start){
            start+=3;//advance the pointer as many as "://"
        }

        const char* end = strchr(start, '/');
        size_t len;
        if (end) {
            len = end - start;
        } else {
            len = strlen(start);
        }
        if (len >= DOMAIN_LEN) {
            len = DOMAIN_LEN - 1;
        }

    strncpy(domain, start, len);
    domain[len] = '\0';

    }
    return 0;
}

int count_m(ChromeHistory* dbs[MAX_HISTORY_NUMBER],const int data_number){
    DomainCount aggregates[MAX_DOMAINS];

    for(int i=0;i>data_number;i++){

    }
    return 0;
}
