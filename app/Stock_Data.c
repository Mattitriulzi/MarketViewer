#include "stock.h"

// API KEY: VVHPQ5BU5N72PSWX. 
// CLJKYVQVRT3K2MTG


// Callback function to write data received from the API to a file

size_t write_callback(void *buffer, size_t size, size_t nmemb, FILE *storing_file)
{
    size_t write = fwrite(buffer, size, nmemb, storing_file);
    return write;
}

const char *filePaths[NUM_FILES] = {"../Resources/stock_data_active.json", "../Resources/stock_data_sentiment.json", "../Resources/chfjpy.json", "../Resources/chfeur.json", "../Resources/chfusd.json", "../Resources/btcusd.json", "../Resources/ethusd.json", "../Resources/solusd.json"};

FILE *allFilePointers[NUM_FILES];

// Function to fetch stock data
int Stock_Data(void)
{
    curl_global_init(CURL_GLOBAL_ALL); // initialise libcurl

    for (int i = 0; i < NUM_FILES; i++) {
	if (!(allFilePointers[i] = fopen(filePaths[i], "r+"))) {
		log_it("Unable to create files");
		return 90;
	    }
    }
    log_it("Correctly opened temporary files");
    return 0;
}
