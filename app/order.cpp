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

    int err;
    err = Stock_Data(); // Call the Stock_Data function
    if(err)
    {
        perror("Error when fetching Stock Data"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        return 800; // Return an error code
    }

    err = json(); // Call the json function
    if (err)
    {
        perror("Error when parsing json file"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        return 802; // Return an error code
    }

    err = SQL(); // Call the SQL function
    if(err)
    {
        perror("Error when creating SQL database"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        return 801; // Return an error code
    }

    err = SQL_read(); // Call the SQL_read function
    if(err)
    {
        perror("Error when reading SQL database"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        return 803; // Return an error code
    }

    err = interface(); // Call the interface function
    if(err)
    {
        perror("Error when starting interface"); // Print an error message if there's an error
        printf("Error code: %d\n", err); // Print the error code
        return 804; // Return an error code
    }

    /*
    err = free_structs();
    if (err)
    {
        perror("Error when freeing the structs");
        return 805;
    }
    */

    return 0; // Return 0 to indicate successful execution
}