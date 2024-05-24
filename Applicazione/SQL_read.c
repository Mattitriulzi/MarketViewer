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
// if true, then the app was already started today and no need to print into the database
bool already_opened = 0; 

int callback(void *p, int argc, char **argv, char**azColName);
int SQL_read(void)
{
    char *errmsg = NULL;
    const char *table_active = "Most_active";
    const char *table_news = "News";

    int rd = sqlite3_exec(db, "SELECT date FROM table_active LIMIT 1 ", callback, 0, &errmsg);
    if (rd)
    {
        perror("Unable to access database");
        return 20;
    }
    if(!already_opened) goto(Stock_read);



    Stock_read:
        for (int i = 0; i < LENGTH_STOCKS; i++)
        {
        char *command = sqlite3_mprintf("INSERT INTO %s Values ('%q', '%q', '%q', '%q', '%q', '%q')",
        table_active,
        (active_stocks + i)->ticker, (active_stocks + i)->price,
        (active_stocks + i)->price_change, (active_stocks + i)->change_percentage,
        (active_stocks + i)->volume, date);

        int rc = sqlite3_exec(db, command, NULL, 0, &errmsg);
        if (rc)
        {
            perror("Unable to access database");
            return 20;
        }
        }
        sqlite3_free(command);
        
        for (int i = 0; i < LENGTH_NEWS; i++)
        {
            char *command = sqlite3_mprintf("INSERT INTO %s VALUES ('%q', '%q', '%q', '%q', '%q')", 
            table_news,
            (sentiments + i)->title, (sentiments + i)->URL,
            (sentiments + i)->summary, (sentiments + i)->sentiment,
            (sentiments + i)->tickers);
            int rc = sqlite3_exec(db, command, NULL, 0,  &errmsg);
            if (rc)
            {
                perror("Unable to access database");
                return 20;
            }
        }
        sqlite3_free(command);
        free(date);
}

int callback(void *p, int argc, char** argv, char** azColName)
{
    int date_position;
    for(date_position = 0; date_position < argc; date_position++)
    {
        if(!strcmp(*(azColName + date_position), "date")) break;
    }
    if (!strcmp(*(argv + date_position), date)) already_opened = 1;
    return 0;
}
