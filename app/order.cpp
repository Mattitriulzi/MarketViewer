#ifdef __cplusplus
extern "C" {
#endif
    #include "stock.h" // Include the "stock.h" header file
#ifdef __cplusplus
}
#endif


int main()
{
    // order of which functions to perform
    log_it("---------------------------------------------------");
    log_it("(MAIN) Starting Application");

    int err;
    err = Stock_Data(); // Call the Stock_Data function
    if(err)
    {
        perror("Error when fetching Stock Data"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        log_it("(MAIN) Error when fetching Stock Data");
        return 800; // Return an error code
    }
    log_it("(MAIN) Successfully fetched Stock Data");

    err = json(); // Call the json function
    if (err)
    {
        perror("Error when parsing json file"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        log_it("(MAIN) Error when parsing json file");
        return 802; // Return an error code
    }
    log_it("(MAIN) Successfully parsed json file");

    err = SQL(); // Call the SQL function
    if(err)
    {
        perror("Error when creating SQL database"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        log_it("(MAIN) Error when creating SQL database");
        return 801; // Return an error code
    }
    log_it("(MAIN) Successfully created SQL database");

    err = SQL_read(); // Call the SQL_read function
    if(err)
    {
        perror("Error when reading SQL database"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        log_it("(MAIN) Error when reading SQL database");
        return 803; // Return an error code
    }
    log_it("(MAIN) Successfully read SQL database");

    err = interface(); // Call the interface function
    if(err)
    {
        perror("Error when starting interface"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        log_it("(MAIN) Error when starting interface");
        return 804; // Return an error code
    }
    log_it("(MAIN) Stopping Application GUI");
    log_it("(MAIN) Successfully closed application GUI");

    
    err = free_structs();
    if (err)
    {
        perror("Error when freeing the structs");
        log_it("(MAIN) Error when freeing the structs");
        return 805;
    }
    log_it("(MAIN) Successfully freed all structure arrays");
    log_it("(MAIN) Successfully stopped the Application");
    log_it("---------------------------------------------------");
    

    return 0; // Return 0 to indicate successful execution
}