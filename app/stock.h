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
/* Change between pointer and array, same behaviors but it will be created in the stack rather
than the heap, allowing for faster software and no need to free after*/
extern stock active_stocks[LENGTH_STOCKS];

extern news sentiments[LENGTH_NEWS];

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

//free_structs function that was needed when the arrays where dynamically allocated
//int free_structs(void);

#ifdef __cplusplus
}
#endif
int interface(void);