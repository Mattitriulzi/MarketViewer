#include "stock.h"

int free_structs(void) 
{
    for (int i = 0; i < LENGTH_NEWS; i++) {
        if (sentiments[i].title) {
            free(sentiments[i].title);
            sentiments[i].title = NULL;
        }
        if (sentiments[i].URL) {
            free(sentiments[i].URL);
            sentiments[i].URL = NULL;
        }
        if (sentiments[i].summary) {
            free(sentiments[i].summary);
            sentiments[i].summary = NULL;
        }
        if (sentiments[i].sentiment) {
            free(sentiments[i].sentiment);
            sentiments[i].sentiment = NULL;
        }
        if (sentiments[i].tickers) {
            free(sentiments[i].tickers);
            sentiments[i].tickers = NULL;
        }
    }

    log_it("Successfully freed News structure array");

    for (int i = 0; i < LENGTH_STOCKS; i++) {
        if (active_stocks[i].ticker) {
            free(active_stocks[i].ticker);
            active_stocks[i].ticker = NULL;
        }
        if (active_stocks[i].price) {
            free(active_stocks[i].price);
            active_stocks[i].price = NULL;
        }
        if (active_stocks[i].price_change) {
            free(active_stocks[i].price_change);
            active_stocks[i].price_change = NULL;
        }
        if (active_stocks[i].change_percentage) {
            free(active_stocks[i].change_percentage);
            active_stocks[i].change_percentage = NULL;
        }
        if (active_stocks[i].volume) {
            free(active_stocks[i].volume);
            active_stocks[i].volume = NULL;
        }
    }

    log_it("Successfully freed Active Stock structure array");
    return 0;
}