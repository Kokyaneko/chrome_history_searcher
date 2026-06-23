#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY_NUMBER 10000

typedef struct {
    char url[2048];//[0]
    char title[1024];//[1]
    int visit_count;//[2]
} ChromeHistory;

int main(int argc,char *argv[]){
    if(argc != 2){
        puts("usage:chrome_history <file name>");
        return 1;
    }

    //check exist file with fopen()
    FILE *fp = fopen(argv[1],"r");
    if(fp==NULL){
        puts("error:file does not exist.");
        return 1;
    }
    fclose(fp);

    sqlite3 *db;
    char *filename = argv[1];
 
    //open database
    if(sqlite3_open(filename, &db) != SQLITE_OK){
        perror("file open");
        return 1;
    }

    // SQL compile
    sqlite3_stmt *stmt;
    const char* com="SELECT url,title,visit_count FROM urls";
    
    if(sqlite3_prepare_v2(db, com, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    ChromeHistory* my_memory_db[10000]; // 1万件分のメモリ上のデータベース
    int i=0;

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        if(i<MAX_HISTORY_NUMBER){
            printf("Loaded %s histories.",i+1);
            break;
        }
        // メモリを確保
        my_memory_db[i] = malloc(sizeof(ChromeHistory));
    
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

    //close database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    for(int j=0;j<i;j++){
        free(my_memory_db[j]);
    }

    return 0;
}
