#pragma once

#define URL_TITLE_LEN 2048

typedef struct {
    char url[URL_TITLE_LEN];
    char title[URL_TITLE_LEN];
    int visit_count;
} ChromeHistory;
