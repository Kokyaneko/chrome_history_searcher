#include <stdio.h>
#include <string.h>
#include "define.h"

//MAX_HISTORY_NUMBER 10000
//MAX_DOMAINS 3000
//DOMAIN_LEN 256

int count_m(ChromeHistory* dbs[MAX_HISTORY_NUMBER],const int data_number){
    DomainCount domains[MAX_DOMAINS];
    for(int i=0;i<MAX_DOMAINS;i++){
        //reset structure
        domains[i].domain[0] = '\0';
        domains[i].count = 0;
    }

    char domain[DOMAIN_LEN];
    int domain_number = 0;

    int i=0;
    for(i;i<data_number;i++){
        if(strstr(dbs[i]->url,"file://") != NULL)continue;//ignore urls:"file://"
        const char *start = strstr(dbs[i]->url,"://");
        if(start){
            start+=3;//get forward the pointer as many as "://"
        }else{
            continue;
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

        int found_index=-1;
        for(int ii=0;ii<MAX_DOMAINS;ii++){
            if(strcmp(domain,domains[ii].domain) == 0){
                found_index = ii;
                break;
            }
        }
        if(found_index == -1 && domain_number < MAX_DOMAINS){
            strcpy(domains[domain_number].domain,domain);
            domains[domain_number].count += dbs[i]->visit_count;
            domain_number++;
        }else{
            domains[found_index].count += dbs[i]->visit_count;
        }
    }

    D_PER counted_per[i];

    int total=0;
    for(int j=0;j<i;j++){
        total += domains[j].count;
    }

    if(i!=0){
        puts("");
        printf("%d domain(s) is(are) counted.\n",domain_number);
        printf("%d URL(s) counted.\n",i);
        puts("------");

        for(int j=0;j<domain_number;j++){
            strcpy(counted_per[j].domain , domains[j].domain);
            counted_per[j].percent = (domains[j].count * 100)/total;
            printf("%s %d(%d%%)\n",domains[j].domain,domains[j].count,counted_per[j].percent); 
        }
        puts("------");
        puts("");
    }else{
        puts("No URL counted");
    }

    return 0;
}
