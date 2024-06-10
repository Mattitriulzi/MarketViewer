#include "stock.h"

sqlite3 *db = NULL;

/* Function to create the database and initialize tables */
int create_database(sqlite3 *db);

/* Function to perform SQL operations */
int SQL(void)
{
    int rc;

    /* Check if database already exists, if not then initialize the tables */
    if (access("Stock_Data.db", R_OK | W_OK) == -1)
    {
        log_it("Database does not exist, creating database and initializing tables");

        /* Initialize database */
        rc = sqlite3_open("Stock_Data.db", &db);
        if (rc)
        {
            perror("Unable to create or open database");
            log_it("Unable to create or open database");
            return 200;
        }

        rc = create_database(db);
        if (rc)
        {
            perror("Unable to initialize tables");
            return 201;
        }
        log_it("Successfully created and initialized tables");
    }
    else
    {
        log_it("Database found, opening database");

        rc = sqlite3_open("Stock_Data.db", &db);
        if (rc)
        {
            perror("Unable to create or open database");
            log_it("Unable to create or open database");
            return 203;
        }
        log_it("Successfully opened database");
    }

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
                       "Tickers TEXT NOT NULL)";

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
