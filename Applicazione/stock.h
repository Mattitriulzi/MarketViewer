#include <jansson.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <curl/multi.h> 
#include <sqlite3.h>
#include <curl/curl.h>
#include <unistd.h>

#define LENGTH_STOCKS  20
#define LENGTH_NEWS 10
#define buffer_len 4096

typedef struct stock
{
    char *ticker;
    char *price;
    char *price_change;
    char *change_percentage;
    char *volume; 
} stock;



typedef struct news
{
    char *title;
    char *URL;
    char *summary;
    char *sentiment;
    char *tickers;

} news;

extern stock *active_stocks;

extern news *sentiments;

extern FILE *stock_data_sentiment;

extern FILE *stock_data_active;

extern sqlite3 *db;

extern char *date;

#ifdef __cplusplus
extern "C" {
#endif
//char *read_file(FILE *file, int length);

int Stock_Data(void);

int SQL_read(void);

int SQL(void);

int json(void);

#ifdef __cplusplus
}
#endif
int interface(void);