
#include "stock.h"

// if true, then the app was already started today and no need to print into the database
bool already_opened = 0; 

int callback_empty(void *count, int argc, char **argv, char** azColName);

int callback(void *p, int argc, char **argv, char **azColName);

int is_table_empty(sqlite3 *db, const char *table_name);

int SQL_read(void)
{
    char *errmsg = NULL;
    const char *table_active = "Most_active";
    const char *table_news = "News";


    if (!is_table_empty(db, table_active))
    {
        int rd = sqlite3_exec(db, "SELECT date FROM Most_active LIMIT 1 ", callback, 0, &errmsg);
        if (rd)
        {
        perror("Unable to access database");
        return 400;
        }
    } 
    // check the date of the last entry to avoid dup entries
    if (date) free(date);
    if(!already_opened) goto Stock_read;
    return 0;



    Stock_read:
        for (int i = 0; i < LENGTH_STOCKS; i++)
        {
            // create a sqlite3 formatted string for the command
            char *command = sqlite3_mprintf("INSERT INTO %s Values ('%q', '%q', '%q', '%q', '%q', '%q')",
            table_active,
            (active_stocks + i)->ticker, (active_stocks + i)->price,
            (active_stocks + i)->price_change, (active_stocks + i)->change_percentage,
            (active_stocks + i)->volume, date);
            // execute the command
            int rc = sqlite3_exec(db, command, NULL, 0, &errmsg);
            if (rc)
            {
                perror("Unable to access database");
                return 20;
            }
            if (command) sqlite3_free(command);
        }
        
        
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
                printf("Error: %s\n", errmsg);
                perror("Unable to access database");
                return 20;
            }
            if (command )sqlite3_free(command);
        }

        if (db) sqlite3_close(db);
        return 0;
}

int callback(void *p, int argc, char** argv, char** azColName)
{
    // callback functions that is called on each row 
    int date_position;
    for(date_position = 0; date_position < argc; date_position++)
    {
        if(!strcasecmp(azColName[date_position], "Date")) break;
    }
    if (!strcasecmp(argv[date_position], date)) already_opened = 1;
    return 0;
}


int is_table_empty(sqlite3 *db, const char *table_name)
{
    // function that will check whether a table is empty
    char *errmsg = NULL;
    int count = 0;
    char *command = sqlite3_mprintf("SELECT Count (*) FROM '%q'", table_name);
    int rc = sqlite3_exec(db, "SELECT Count (*) FROM Most_active", callback_empty, &count, &errmsg);
    if (rc != SQLITE_OK)
    {
        perror("cannot execute demand (table_empty_check)");
        if (command) sqlite3_free(command);
        return -1;
    }
    if (command) sqlite3_free(command);
    if (!count) return 1;
    return 0;
}



int callback_empty(void *count, int argc, char **argv, char **azColName)
{
    *(int *)count = atoi(argv[0]);
    return 0;
}