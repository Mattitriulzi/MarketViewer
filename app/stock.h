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

// Structs for the stock and news data
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

// extern stock *active_stocks;
extern stock active_stocks[LENGTH_STOCKS];

// extern news *sentiments;
extern news sentiments[LENGTH_NEWS];

extern FILE *stock_data_sentiment;

extern FILE *stock_data_active;

extern FILE *log_file;

extern sqlite3 *db;

extern char *date;

#ifdef __cplusplus
extern "C" {
#endif
// old read file function
//char *read_file(FILE *file, int length);

int Stock_Data(void);

int SQL_read(void);

int SQL(void);

int json(void);

void log_it(const char *msg);
// the log_it function already adds a new line so the message should not have the escape seq

int free_structs(void);

int json_parse_active(json_t *root_active);

int json_parse_sentiment(json_t*root_news);

#ifdef __cplusplus
}
#endif
int interface(void);

#define check(a, b) do{ if(!a) return b;} while(0)