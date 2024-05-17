#include "stock.h"


// sentiments, active_stocks
/*typedef struct stock
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
*/
int SQL_read(void)
{
    const char *table_active = "Most_active";
    const char *table_news = "News";

    for (int i = 0; i < LENGTH_STOCKS; i++)
    {

    int rc = sqlite_exec(db,"INSERT INTO %s Values (%s, %s, %s, %s, %s)", table_active,
    (active_stocks + i)->ticker, (active_stocks + i)->price,
    (active_stocks + i)->price_change, (active_stocks + i)->change_percentage,
    (active_stocks + i)->volume);
    if (rc)
    {
        perror("Unable to access database");
        return 20;
    }
    }
    
    for (int i = 0; i < LENGTH_NEWS; i++)
    {
        int rc = sqlite_exec(db,"INSERT INTO %s VALUES (%s, %s, %s, %s, %s)", table_news,
        (news + i)->title, (news + i)->URL,
        (news + i)->summary; (news + i)->sentiment,
        (news + i)->tickers);
        if (rc)
        {
            perror("Unable to access database");
            return 20;
        }
    }
}