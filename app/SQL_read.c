#include "stock.h"

// if true, then the app was already started today and no need to print into the database
bool already_opened = 0; 

// Function prototypes
int callback_empty(void *count, int argc, char **argv, char** azColName);

int callback(void *p, int argc, char **argv, char **azColName);

int is_table_empty(sqlite3 *db, const char *table_name);

int SQL_read(void);

int SQL_read(void)
{
    char *errmsg = NULL;
    const char *table_active = "Most_active";
    const char *table_news = "News";

    log_it("Checking if the database is empty");
    
    if (is_table_empty(db, table_active)) {
        log_it("Database is empty");
        goto Stock_Read;
    }
    
    log_it("Database is not empty, checking if app was already opened today");
    
    int rd = sqlite3_exec(db, "SELECT date FROM Most_active LIMIT 1", callback, 0, &errmsg);
    if (rd){
        perror("Unable to access database");
        log_it("Unable to access database");
        return 400;
    }



    if(!already_opened) {
        log_it("App was not opened today");
        goto Stock_Read;
    }
    
    log_it("App was already opened today, no need to update database");
    if (db) {
        sqlite3_close(db);
        db = NULL;
    }
    log_it("Database closed successfully");
    if (date){
        free(date);
        date = NULL;
    }
    log_it("No update was necessary");

    return 0;

    // Label to jump to if the app was not already opened today
    Stock_Read:
        log_it("Starting the database update process");
        log_it("Reading data from the structure arrays");

        log_it("Starting to insert Active Stocks array in database");

        for (int i = 0; i < LENGTH_STOCKS; i++)
        {
            // Create a sqlite3 formatted string for the command to insert data into the 'Most_active' table
            char *command = sqlite3_mprintf("INSERT INTO %s Values ('%q', '%q', '%q', '%q', '%q', '%q')",
            table_active,
            active_stocks[i].ticker, active_stocks[i].price,
            active_stocks[i].price_change, active_stocks[i].change_percentage,
            active_stocks[i].volume, date);
            
            // Execute the command to insert data into the 'Most_active' table
            int rc = sqlite3_exec(db, command, NULL, 0, &errmsg);
            if (rc)
            {
                perror("Unable to access database");
                log_it("Unable to access database");
                return 20;
            }
            if (command) {
                sqlite3_free(command);
                command = NULL;
            }
        }
        log_it("Successfully inserted the Active Stock structure array in database");

        log_it("Starting to insert News structure array in database");
        
        for (int i = 0; i < LENGTH_NEWS; i++)
        {
            // Create a sqlite3 formatted string for the command to insert data into the 'News' table
            char *command = sqlite3_mprintf("INSERT INTO %s VALUES ('%q', '%q', '%q', '%q', '%q', '%q')", 
            table_news,
            sentiments[i].title, sentiments[i].URL,
            sentiments[i].summary, sentiments[i].sentiment,
            sentiments[i].tickers, date);
            
            // Execute the command to insert data into the 'News' table
            int rc = sqlite3_exec(db, command, NULL, 0,  &errmsg);
            if (rc)
            {
                printf("Error: %s\n", errmsg);
                perror("Unable to access database");
                log_it("Unable to access database");
                return 20;
            }
            if (command) {
                sqlite3_free(command);
                command = NULL;
            }
        }
        log_it("Successfully inserted the News structure array in database");

        if (db) {
            sqlite3_close(db);
            db = NULL;
        }

        if (date) {
            free(date);
            date = NULL;
        }

        log_it("Database closed successfully");
        return 0;
}

// Callback function for the SQL query to check the date of the last entry
int callback(void *p, int argc, char** argv, char** azColName)
{
    // Find the position of the 'Date' column in the result set
    int date_position;
    for(date_position = 0; date_position < argc; date_position++)
    {
        if(!strcasecmp(azColName[date_position], "Date")) break;
    }
    // Check if the date of the last entry is the same as the current date
    if (!strcasecmp(argv[date_position], date)) already_opened = 1;
    log_it("Compared current date with last date in database");
    return 0;
}


// Function to check if a table is empty
int is_table_empty(sqlite3 *db, const char *table_name)
{
    char *errmsg = NULL;
    int count = 0;
    
    // Create the SQL command to count the number of rows in the table
    char *command = sqlite3_mprintf("SELECT Count (*) FROM '%q'", table_name);
    
    // Execute the command and pass the count variable as a callback parameter
    int rc = sqlite3_exec(db, "SELECT Count (*) FROM Most_active", callback_empty, &count, &errmsg);
    if (rc != SQLITE_OK)
    {
        perror("cannot execute demand (table_empty_check)");
        log_it("cannot execute demand (table_empty_check)");
        if (command) sqlite3_free(command);
        return -1;
    }
    if (command) {
        sqlite3_free(command);
        command = NULL;
    }
    
    // Return 1 if the table is empty, 0 otherwise
    if (!count) return 1;
    return 0;
}


// Callback function for the SQL query to count the number of rows in a table
int callback_empty(void *count, int argc, char **argv, char **azColName)
{
    // Convert the count value from string to integer
    *(int *)count = atoi(argv[0]);
    return 0;
}