#pragma once

#define MAX_HISTORY_NUMBER 10000
#define MAX_COMMAND_LEN 1024
#define URL_TITLE_LEN 2048
#define DOMAIN_LEN 256
#define MAX_DOMAINS 3000

typedef struct {
    char url[URL_TITLE_LEN];
    char title[URL_TITLE_LEN];
    int visit_count;
} ChromeHistory;

typedef struct {
    char domain[DOMAIN_LEN];
    int count;
} DomainCount;

typedef struct {
    char domain[DOMAIN_LEN];
    float percent;
} D_PER;
