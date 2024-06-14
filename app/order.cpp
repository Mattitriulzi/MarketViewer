#ifdef __cplusplus
extern "C" {
#endif
    #include "stock.h" 
#ifdef __cplusplus
}
#endif


int main(void)
{
    // order of which functions to perform
    log_it(NULL);
    log_it("---------------------------------------------------");
    log_it(" ");
    log_it("(MAIN) Starting Application");

    int err;
    err = Stock_Data(); 
    if(err)
    {
        perror("Error when fetching Stock Data"); 
        printf("Error code: %d\n", err); 
        log_it("(MAIN) Error when fetching Stock Data, exiting");
        return 800; 
    }
    log_it("(MAIN) Successfully fetched Stock Data");
    log_it(" ");
    log_it("(MAIN) Starting json file parsing");
    err = json(); 
    if (err)
    {
        perror("Error when parsing json file"); 
        printf("Error code: %d\n", err); 
        log_it("(MAIN) Error when parsing json file, exiting");
        return 802; 
    }
    log_it("(MAIN) Successfully parsed json file");
    log_it(" ");
    log_it("(MAIN) Checking the database's existence");
    err = SQL(); 
    if(err)
    {
        perror("Error when creating SQL database"); 
        printf("Error code: %d\n", err); 
        log_it("(MAIN) Error when creating SQL database, exiting");
        return 801; 
    }
    log_it("(MAIN) Successfully created SQL database");
    log_it(" ");
    log_it("(MAIN) Starting database update process");
    err = SQL_read(); 
    if(err)
    {
        perror("Error when reading SQL database"); 
        printf("Error code: %d\n", err); 
        log_it("(MAIN) Error when reading SQL database, exiting");
        return 803; 
    }

    log_it("(MAIN) Successfully updated database if necessary");
    log_it(" ");
    log_it("(MAIN) Starting Application GUI");
    err = interface(); 
    if(err)
    {
        perror("Error when starting interface"); 
        printf("Error code: %d\n", err); 
        log_it("(MAIN) Error when starting interface");
        return 804; 
    }
    log_it("(MAIN) Successfully closed application GUI");
    log_it(" ");
    
    log_it("(MAIN) Starting the freeing process");
    err = free_structs();
    if (err)
    {
        perror("Error when freeing the structs");
        log_it("(MAIN) Error when freeing the structs");
        return 805;
    }
    log_it("(MAIN) Successfully freed all structure arrays");
    log_it("(MAIN) Successfully stopped the Application");
    log_it(" ");
    log_it("---------------------------------------------------");
    log_it(NULL);
    

    return 0; 
}