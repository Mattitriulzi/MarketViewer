#include "stock.h"

// API KEY: VVHPQ5BU5N72PSWX. 
// CLJKYVQVRT3K2MTG


// Callback function to write data received from the API to a file

size_t write_callback(void *buffer, size_t size, size_t nmemb, FILE *storing_file)
{
    size_t write = fwrite(buffer, size, nmemb, storing_file);
    return write;
}

char *filePaths[NUM_FILES] = {"../stock_data_active.json", "../stock_data_sentiment.json", "../chfjpy.json", "../chfeur.json", "../chfusd.json", "../btcusd.json", "../ethusd.json", "../solusd.json"};

FILE *allFilePointers[NUM_FILES];

// Function to fetch stock data
int Stock_Data(void)
{
    curl_global_init(CURL_GLOBAL_ALL); // initialise libcurl

    for (int i = 0; i < NUM_FILES; i++) {
	if (!(allFilePointers[i] = fopen(filePaths[i], "w+"))) {
		log_it("Unable to create files");
		return 90;
	    }
    }
    log_it("Correctly opened temporary files");

    CURLM *multi_curl = curl_multi_init();
    CURL *curls[NUM_FILES];
    for (int i = 0; i < NUM_FILES; i++) {
        curls[i] = curl_easy_init();
        if (!curls[i]) {
            log_it("unable to initiate research, probably missing memory");
            return 91;
        }

    }

    log_it("Setting up for libcurl transfers");

    char *apiLinks[NUM_FILES] = {"https://www.alphavantage.co/query?function=TOP_GAINERS_LOSERS&apikey=VVHPQ5BU5N72PSWX",
    "https://www.alphavantage.co/query?function=NEWS_SENTIMENT&topics=finance&sort=latest,relevance_score_definition&limit=15&apikey=VVHPQ5BU5N72PSWX",
    "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=CHF&to_currency=JPY&apikey=VVHPQ5BU5N72PSWX",
    "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=CHF&to_currency=EUR&apikey=VVHPQ5BU5N72PSWX",
    "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=CHF&to_currency=USD&apikey=VVHPQ5BU5N72PSWX",
    "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=BTC&to_currency=USD&apikey=VVHPQ5BU5N72PSWX",
    "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=ETH&to_currency=USD&apikey=VVHPQ5BU5N72PSWX",
    "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=SOL&to_currency=USD&apikey=VVHPQ5BU5N72PSWX"
    };

    for (int i = 0 ; i < NUM_FILES; i++) {
	curl_easy_setopt(curls[i], CURLOPT_URL, apiLinks[i]);
	curl_easy_setopt(curls[i], CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curls[i], CURLOPT_WRITEDATA, allFilePointers[i]);
	curl_multi_add_handle(multi_curl, curls[i]);
    }

    log_it("Correctly set up the curl transfers");

    // Run all transfers!
    int still_running;
    do 
    {
        CURLMcode mc = curl_multi_perform(multi_curl, &still_running);
        // Start reading the easy curls

        if (!mc && still_running) mc = curl_multi_poll(multi_curl, NULL, 0, 1000, NULL);
        /* Perform the easy curls */

        if (mc)
        /* Error checking */
        {
            perror("curl_multi_poll function was unable to perform transfers");
            log_it("curl_multi_poll function was unable to perform transfers");
            return 103;
        }
    } while(still_running);

    /* Continue until there are no more tranfers to be done */
    log_it("Correctly fetched data from the API");

    for (int i = 0; i < NUM_FILES; i++) {
	    if (curls[i]) {
		    curl_easy_cleanup(curls[i]);
		    curls[i] = NULL;
	    }
    }

    if (multi_curl) {
	    curl_multi_cleanup(multi_curl);
	    multi_curl = NULL;
    }

    curl_global_cleanup();

    // Flush the buffers
    log_it("Correctly cleaned up memory");
    // flush all buffers and set the file reader to the beginning of the files
    for (int i = 0; i < NUM_FILES; i++) {
	    fflush(allFilePointers[i]);
	    if (fseek(allFilePointers[i], 0, SEEK_SET)) {
		    log_it("Unable to move file pointer to the beginning of file");
		    return 105;
	    }
    }

    log_it("Successfully prepared files for reading");
    return 0;
}
