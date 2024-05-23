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

stock *active_stocks;

typedef struct news
{
    char *title;
    char *URL;
    char *summary;
    char *sentiment;
    char *tickers;

} news;

news *sentiments;

FILE *stock_data_sentiment;

FILE *stock_data_active;

sqlite3 *db;

char *date;

char *read_file(FILE *file, int length);
