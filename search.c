#include <stdio.h>
#include <string.h>
#include "struct.h"

#define MAX_HISTORY_NUMBER 10000
#define URL_TITLE_LEN 2048

int search_r(char url[URL_TITLE_LEN],char title[URL_TITLE_LEN],ChromeHistory* dbs[MAX_HISTORY_NUMBER],const int data_number){
    int result_count=0;
    
    for(int i=0;i<data_number;i++){
        if (dbs[i] == NULL) continue;//memory check

        if(url && strstr(dbs[i]->url,url) == NULL)continue;
        if(title && strstr(dbs[i]->title,title) == NULL)continue;

        printf("%s , %s , %d\n",dbs[i]->url,dbs[i]->title,dbs[i]->visit_count);
        result_count++;
    }

    puts("");
    if(result_count == 0)puts("No URL found.");
    else printf("%d URL(s) found.\n",result_count);
    puts("");

    return 0;
}

int search_m(ChromeHistory* dbs[MAX_HISTORY_NUMBER],const int data_number){
    char url[URL_TITLE_LEN],title[URL_TITLE_LEN];

    printf("search URL:> ");
    fgets(url,sizeof(url),stdin);
   
    printf("search Title:> ");
    fgets(title,sizeof(title),stdin);

    //disable "<input>\n"
    url[strcspn(url, "\n")] = '\0';
    title[strcspn(title, "\n")] = '\0';

    search_r(url,title,dbs,data_number);

    return 0;
}
