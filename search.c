#include <stdio.h>
#include <readline/readline.h>
#include <string.h>
#include "define.h"

//MAX_HISTORY_NUMBER 10000
//URL_TITLE_LEN 2048

int search_r(char url[URL_TITLE_LEN],char title[URL_TITLE_LEN],ChromeHistory* dbs[MAX_HISTORY_NUMBER],const int data_number){
    int result_count=0;
    
    puts("------");

    for(int i=0;i<data_number;i++){
        if (dbs[i] == NULL) continue;//memory check

        if(url && strstr(dbs[i]->url,url) == NULL)continue;
        if(title && strstr(dbs[i]->title,title) == NULL)continue;

        printf("%s , %s , %d\n",dbs[i]->url,dbs[i]->title,dbs[i]->visit_count);
        result_count++;
        puts("");
    }

    if(result_count == 0){
        puts("No URL found.");
    }else{
        puts("------");
        printf("%d URL(s) found.\n",result_count);
    }

    puts("------");
    puts("");

    return 0;
}

int search_m(ChromeHistory* dbs[MAX_HISTORY_NUMBER],const int data_number){
    char * url = readline("search URL>");
    char * title = readline("search title>");

    search_r(url,title,dbs,data_number);

    return 0;
}
