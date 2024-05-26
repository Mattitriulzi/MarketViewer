#ifdef __cplusplus
extern "C" {
#endif
    #include "stock.h"
#ifdef __cplusplus
}
#endif


int main()
{
    // order of which functions to perform
    int err;

    err = Stock_Data();
    if(err)
    {
        perror("Error when fetching Stock Data");
        return 800;
    }
    
    err = json();
    if (err)
    {
        perror("Error when parsing json file");
        printf("Error code: %d\n", err);
        return 802;
    }
    
    err = SQL();
    if(err)
    {
        perror("Error when creating SQL database");
        return 801;
    }

    

    err = SQL_read();
    if(err)

    {
        perror("Error when reading SQL database");
        return 803;
    }

    err = interface();
    if(err)
    {
        perror("Error when starting interface");
        return 804;
    }

    return 0;
}