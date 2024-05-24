#include "stock.h"

int main()
{
    int err;

    err = Stock_Data();
    if(!err)
    {
        perror("Error when fetching Stock Data");
        return 300;
    }
    
    err = SQL();
    if(!err)
    {
        perror("Error when creating SQL database");
        return 301;
    }

    err = json();
    if (!err)
    {
        perror("Error when parsing json file");
        return 302;
    }

    err = SQL_read();
    if(!err)

    {
        perror("Error when reading SQL database");
        return 303;
    }

    err = interface();
    if(!err)
    {
        perror("Error when starting interface");
        return 304;
    }

    return 0;
}