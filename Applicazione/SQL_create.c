#ifdef _cplusplus
extern "C" {
    #endif  

#include "stock.h"

/*temporary files were created in the header file, respectively stock_data_active and stock_data_sentiment*/

int create_database(sqlite3 *db);

int SQL(void)
{
    /*initialise database*/
    int rc = sqlite3_open("Stock_Data", &db);
    if (rc)
    {
     perror("Unable to create or open database");
     return 200;
    }
 


    /*Check if database already exists, if not then initialise the tables*/
    if (access("Stock_Data", R_OK | W_OK))
    {
        rc = create_database(db);
        if (rc)
        {
            perror("Unable to initialise tables");
            return 201;
        }
    }

    return 0;

}







int create_database(sqlite3 *db)
{
    char *zErrMsg;
    char *table_active = "CREATE TABLE Most_Active("\
                        "Ticker TEXT NOT NULL," \
                        "Price FLOAT NOT NULL," \
                        "Price_Change FLOAT NOT NULL," \
                        "Change_Percentage TEXT NOT NULL," \
                        "Volume LONG NOT NULL," \
                        "Date TEXT NOT NULL)";

    char *table_news = "CREATE TABLE News(" \
                        "Title TEXT NOT NULL," \
                        "URL TEXT NOT NULL," \
                        "Summmary TEXT NOT NULL, " \
                        "Sentiment TEXT NOT NULL, " \
                        "Tickers TEXT NOT NULL)";

    /*Execute the creation of the tables in the database*/
    int rc = sqlite3_exec(db, table_active, NULL, 0, &zErrMsg);
    if (rc)
    {
        perror(zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }
    rc = sqlite3_exec(db, table_news, NULL, 0, &zErrMsg);
    if (rc) 
    {
        perror(zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }   

    return 0;
}
#ifdef __cplusplus
}
#endif