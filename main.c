#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

//MAX_HISTORY_NUMBER 10000
//MAX_COMMAND_LEN 1024

int search_r(char url[URL_TITLE_LEN],char title[URL_TITLE_LEN],ChromeHistory* dbs[MAX_HISTORY_NUMBER],const int data_number);

int search_m(ChromeHistory* dbs[MAX_HISTORY_NUMBER],const int data_number);

int count_m(ChromeHistory* dbs[MAX_HISTORY_NUMBER],const int data_number);

int file_exist_check(char* f_name){
    //check exist file with fopen()
    FILE *fp = fopen(f_name,"r");
    
    if(fp==NULL){
        puts("Error:File does not exist.");
        return 1;
    }

        puts("File exists.");
        fclose(fp);
        return 0;
}


int main(int argc,char *argv[]){
    if(argc != 2){
        puts("usage:chrome_history <file name>");
        return 1;
    }

    if(file_exist_check(argv[1]) == 1) return 1;

    sqlite3 *db;
    char *filename = argv[1];
 
    //open database
    if(sqlite3_open(filename, &db) != SQLITE_OK){
        perror("file open");
        return 1;
    }
    else puts("File opned with SQLite.");

    // SQL compile
    sqlite3_stmt *stmt;
    const char* com="SELECT url,title,visit_count FROM urls";
    
    if(sqlite3_prepare_v2(db, com, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    ChromeHistory* my_memory_db[10000];//10000 columns
    int i=0;

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        if(i>=MAX_HISTORY_NUMBER){
            printf("Loaded %s histories.",i+1);
            break;
        }
        // メモリを確保
        my_memory_db[i] = malloc(sizeof(ChromeHistory));

        //メモリへのコピー動作を関数にしてもいいのでは?

        //copy to memory
        //urls
        const char* url_data=(const char*)sqlite3_column_text(stmt, 0);
        if(url_data){
            strncpy(my_memory_db[i]->url,url_data,sizeof(my_memory_db[i]->url) - 1);
        }else{
            strcpy(my_memory_db[i]->title, "");
        }

        //title
        const char* title_data=(const char*)sqlite3_column_text(stmt, 1);
        if(title_data){
            strncpy(my_memory_db[i]->title,title_data,sizeof(my_memory_db[i]->title) - 1);
        }else{
            strcpy(my_memory_db[i]->title, "");
        }

        //visit_count
        my_memory_db[i]->visit_count = sqlite3_column_int(stmt, 2);

        i++;
    }
    printf("Loaded %d histories!\n",i);
    const int data_number = i;

    //close database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    //Main Window
    char command_s[MAX_COMMAND_LEN];
    char* com_s = command_s;

    puts("======");
    puts("Wellcome to Chrome History DB!");
    puts("------");

    while(114514){
        puts("1:Exit");
        puts("2:search");
        puts("3:count");

        printf("chrome history DB> ");
        fgets(com_s,MAX_COMMAND_LEN,stdin);
        int com_i = atoi(com_s);

        if(com_i==0){
            puts("Error : Enter number 1-2");
        }else if(com_i==1){
            return 0;
        }else if(com_i==2){
            search_m(my_memory_db,data_number);
        }else if(com_i==3){
            count_m(my_memory_db,data_number); 
        }else{
            puts("Error : Enter number 1-2");
        }
    }

    for(int j=0;j<i;j++){
        free(my_memory_db[j]);
    }

    return 0;
}
