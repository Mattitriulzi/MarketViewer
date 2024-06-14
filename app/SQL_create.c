#include "stock.h"

sqlite3 *db = NULL;

/* Function to create the database and initialize tables */
int create_database(sqlite3 *db);

/* Function to perform SQL operations */
int SQL(void)
{
    int rc;
    unsigned dbex = 1; //database existence

    if (access("../stockdata.db", R_OK | W_OK) == 1)
        dbex = 0;

    rc = sqlite3_open("../stockdata.db", &db);
    if (rc){
        perror("Unable to create or open database");
        log_it("Unable to create or open database");
        return 200;
    }
    log_it("Opening Database, checking for initialisation");

    if (!dbex){
        log_it("Creating database and initialising tables");
        rc = create_database(db);
        if (rc){
            perror("Unable to initialize tables");
            return 201;
        }
        log_it("Successfully created and initialised tables");
        return 0;
    }

    log_it("Database already initialised");
    return 0;

 
}


/* Function to create the database and initialize tables */
int create_database(sqlite3 *db)
{
    char *zErrMsg;
    char *table_active = "CREATE TABLE Most_Active("
                         "Ticker TEXT NOT NULL,"
                         "Price FLOAT NOT NULL,"
                         "Price_Change FLOAT NOT NULL,"
                         "Change_Percentage TEXT NOT NULL,"
                         "Volume LONG NOT NULL,"
                         "Date TEXT NOT NULL)";

    char *table_news = "CREATE TABLE News("
                       "Title TEXT NOT NULL,"
                       "URL TEXT NOT NULL,"
                       "Summary TEXT NOT NULL, "
                       "Sentiment TEXT NOT NULL, "
                       "Tickers TEXT NOT NULL, "
                       "Date TEXT NOT NULL)";

    /* Execute the creation of the tables in the database */
    int rc = sqlite3_exec(db, table_active, NULL, 0, &zErrMsg);
    if (rc)
    {
        perror(zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }

    log_it("Correctly created the Most_Active table");

    rc = sqlite3_exec(db, table_news, NULL, 0, &zErrMsg);
    if (rc)
    {
        perror(zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }

    log_it("Correctly created the News table");

    return 0;
}
