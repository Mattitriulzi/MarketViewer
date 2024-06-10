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

    /*temporary files were created in the header file, respectively stock_data_active and stock_data_sentiment*/

    // Open temporary file for active stock data
    stock_data_active = fopen("stock_data_active.json", "w+");
    if (!stock_data_active)
    {
        perror("Unable to create Temporary File, probably missing memory");
        log_it("Unable to create Temporary File, probably missing memory");
        return 100;
    }

    // Open temporary file for stock sentiment data
    stock_data_sentiment = fopen("stock_data_sentiment.json", "w+");
    if (!stock_data_sentiment)
    {
        perror("Unable to create Temporary File, probably missing memory");
        log_it("Unable to create Temporary File, probably missing memory"); 
        return 100;
    }

    log_it("Correctly opened temporary files");

    // Generate the curls which will be used to transfer the stock info and initialise them + check for error
    CURL *curl1 = curl_easy_init(); // first transfer
    CURL *curl2 = curl_easy_init(); // second trasfer
    CURLM *multi_curl = curl_multi_init(); // libcurl multi to allow for both transfers to occur simultaneaously
    if (curl1 == NULL || curl2 == NULL || multi_curl == NULL)
    {
        perror("Unable to initiate research, probably missing memory");
        log_it("Unable to initiate research, probably missing memory");
        return 101;
    }

    // Set the settings for the transfers
    // First curl gets the TOP_GAINERS_LOSERS and most active stocks, both write into temporary files
    curl_easy_setopt(curl1, CURLOPT_URL, "https://www.alphavantage.co/query?function=TOP_GAINERS_LOSERS&apikey=VVHPQ5BU5N72PSWX");
    curl_easy_setopt(curl1, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl1, CURLOPT_WRITEDATA, stock_data_active);

    // Second curl gets the current news on chosen subjects
    curl_easy_setopt(curl2, CURLOPT_URL,
    "https://www.alphavantage.co/query?function=NEWS_SENTIMENT&topics=finance&sort=latest,relevance_score_definition&limit=15&apikey=VVHPQ5BU5N72PSWX");
    curl_easy_setopt(curl2,CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl2, CURLOPT_WRITEDATA, stock_data_sentiment);

    // Add the singular easy curl transfers to the multi_curl for simultaneaous transfer
    curl_multi_add_handle(multi_curl, curl1);
    curl_multi_add_handle(multi_curl, curl2);

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

    /* Cleaning up memory */
    curl_easy_cleanup(curl1);
    curl_easy_cleanup(curl2);
    curl_multi_cleanup(multi_curl);
    curl_global_cleanup();

    fclose(stock_data_active);
    fclose(stock_data_sentiment);

    // Reopen files for reading
    stock_data_active = fopen("stock_data_active.json", "r");
    stock_data_sentiment = fopen("stock_data_sentiment.json", "r");
    if (!stock_data_active || !stock_data_sentiment)
    {
        perror("Unable to reopen files for reading");
        log_it("Unable to reopen files for reading");
        return 104;
    }

    log_it("Correctly cleaned up memory, closed, and reopened files for reading");

    return 0;
}
