#pragma once

#define URL_TITLE_LEN 2048
#define DOMAIN_LEN 256

typedef struct {
    char url[URL_TITLE_LEN];
    char title[URL_TITLE_LEN];
    int visit_count;
} ChromeHistory;

typedef struct {
    char domain[DOMAIN_LEN];
    int count;
} DomainCount;
