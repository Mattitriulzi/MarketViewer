
#include "stock.h"

// API KEY: VVHPQ5BU5N72PSWX. 
// CLJKYVQVRT3K2MTG

size_t write_callback(void *buffer, size_t size, size_t nmemb, FILE *storing_file)
{
    printf("writing data to a file\n");
    size_t write = fwrite(buffer, size, nmemb, storing_file);
    return write;
}

FILE *stock_data_active = NULL;
FILE *stock_data_sentiment = NULL;




int Stock_Data(void)
{
    curl_global_init(CURL_GLOBAL_ALL); // initialise libcurl

    /*temporary files were created in the header file, respectively stock_data_active and stock_data_sentiment*/

    stock_data_active = fopen("stock_data_active.json", "w+");
    if (stock_data_active == NULL)
    {
            perror("Unable to create Temporary File, probably missing memory");
            return 100;
    }

    stock_data_sentiment = fopen("stock_data_sentiment.json", "w+");
    if (stock_data_sentiment == NULL)
    {
        perror("Unable to create Temporary File, probably missing memory");
        return 100;
    }

    return 0;


}

