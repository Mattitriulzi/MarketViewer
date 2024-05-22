#include "stock.h"

// API KEY: VVHPQ5BU5N72PSWX. 

size_t write_callback(void *buffer, size_t size, size_t nmemb, FILE *storing_file)
{
    size_t write = fwrite(buffer, size, nmemb, storing_file);
    return write;
}



int Stock_Data(void)
{
    curl_global_init(CURL_GLOBAL_ALL); // initialise libcurl

    /*temporary files were created in the header file, respectively stock_data_active and stock_data_sentiment*/
    stock_data_active  = tmpfile();
    if (stock_data_active == NULL)
    {
            perror("Unable to create Temporary File, probably missing memory");
            return 1;
    }

    stock_data_sentiment = tmpfile();
    if (stock_data_sentiment == NULL)
    {
    perror("Unable to create Temporary File, probably missing memory");
    return 1;
    }

    // generate the curls which will be used to transfer the stock info and initialise them + check for error
    CURL *curl1 = curl_easy_init(); // first transfer
    CURL *curl2 = curl_easy_init(); // second trasfer
    CURLM *multi_curl = curl_multi_init(); // libcurl multi to allow for both transfers to occur simultaneaously
    if (curl1 == NULL || curl2 == NULL || multi_curl == NULL)
    {
        perror("Unable to initiate research, probably missing memory");
        return 2;
    }
    // get the settings for the transfers
    // first gets the TOP_GAINERS_LOSERS and most active stocks, both write into temporary files
    curl_easy_setopt(curl1, CURLOPT_URL, "https://www.alphavantage.co/query?function=TOP_GAINERS_LOSERS&apikey=VVHPQ5BU5N72PSWX");
    curl_easy_setopt(curl1, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl1, CURLOPT_WRITEDATA, stock_data_active);
    // second gets the current news on chosen subjects
    curl_easy_setopt(curl2, CURLOPT_URL,
     "https://www.alphavantage.co/query?function=NEWS_SENTIMENT&topics=finance&sort=latest,relevance_score_definition&limit=15&apikey=VVHPQ5BU5N72PSWX");
     curl_easy_setopt(curl2,CURLOPT_WRITEFUNCTION, write_callback);
     curl_easy_setopt(curl2, CURLOPT_WRITEDATA, stock_data_sentiment);

    // add the singular easy curl transfers to the multi_curl for simultaneaous transfer
    curl_multi_add_handle(multi_curl, curl1);
    curl_multi_add_handle(multi_curl, curl2);

    //run all transfers!
    int still_running;
    do 
    {
        CURLMcode mc = curl_multi_perform(multi_curl, &still_running);
        // start reading the easy curls

        if (!mc && still_running) mc = curl_multi_poll(multi_curl, NULL, 0, 1000, NULL);
        /*perform the easy curls*/

        if (mc)
        /*error checking*/
        {
            perror("curl_multi_poll function was unable to perform transfers");
            return 3;
        }
    } while(still_running);
    /*continue until there are no more tranfers to be done*/



    /*cleaning up memory*/
    curl_easy_cleanup(curl1);
    curl_easy_cleanup(curl2);
    curl_multi_cleanup(multi_curl);
    curl_global_cleanup();

    free(curl1);
    free(curl2);
    free(multi_curl);
    return 0;


}
