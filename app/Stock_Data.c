#include "stock.h"

// API KEY: VVHPQ5BU5N72PSWX. 
// CLJKYVQVRT3K2MTG

// Callback function to write data received from the API to a file
size_t write_callback(void *buffer, size_t size, size_t nmemb, FILE *storing_file)
{
    size_t write = fwrite(buffer, size, nmemb, storing_file);
    return write;
}

// File pointers for storing the stock data
FILE *stock_data_active = NULL;
FILE *stock_data_sentiment = NULL;

// Function to fetch stock data
int Stock_Data(void)
{
    curl_global_init(CURL_GLOBAL_ALL); // initialise libcurl

    stock_data_active = fopen("../stock_data_active.json", "w+");
    stock_data_sentiment = fopen("../stock_data_sentiment.json", "w+");
    if (!stock_data_sentiment || !stock_data_active) {
        perror("Unable to create temporary file, probably missing memory");
        log_it("Unable to create temporary file, stopping");
        return 100;
    }

    log_it("Correctly opened temporary files");
    log_it("Successfully prepared files for reading");
    return 0;
}
