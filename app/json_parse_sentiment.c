#include "stock.h"


int json_parse_sentiment(json_t *root_news){
        /*Time to star the deloading for the news json file, first we will extract the array containing the news and then
    take what interests us */
    json_t *feed_array = json_object_get(root_news, "feed"); // extract the feed from the json giant object
    if (!json_is_array(feed_array))
    {
        perror("Feed is not an object");
        log_it("Feed is not an object");
        json_decref(root_news);
        return 311;
    }


    for (int i = 0; i < json_array_size(feed_array); i++)
    {
        const char *title, *url, *summary, *sentiment; // tickers is a special case, hence will initialise later
        json_t *feed = json_array_get(feed_array, i);
        if (!json_is_object(feed))
        {
            perror("Error when reading object array");
            log_it("Error when reading object array");
            json_decref(root_news);
            return 312;
        }


        json_t *title_json = json_object_get(feed, "title");
        if (!json_is_string(title_json))
        {
            perror("Error when reading object array");
            log_it("Error when reading object array");
            json_decref(root_news);
            return 313;
        }
        title = json_string_value(title_json);
        sentiments[i].title = strdup(title);


        json_t *url_json = json_object_get(feed, "url");
        if(!json_is_string(url_json))
        {
            perror("Error when reading object array");
            log_it("Error when reading object array");
            json_decref(root_news);
            return 314;
        }
        url = json_string_value(url_json);
        sentiments[i].URL = strdup(url);


        json_t *summary_json = json_object_get(feed, "summary");
        if(!json_is_string(summary_json))
        {
            perror("Error when reading object array");
            log_it("Error when reading object array");
            json_decref(root_news);
            return 315;
        }
        summary = json_string_value(summary_json);
        sentiments[i].summary = strdup(summary);


        json_t *sentiment_json = json_object_get(feed, "overall_sentiment_label");
        if(!json_is_string(sentiment_json))
        {
            perror("Error when reading object array");
            log_it("Error when reading object array");
            json_decref(root_news);
            return 316;
        }
        sentiment = json_string_value(sentiment_json);
        sentiments[i].sentiment = strdup(sentiment);


        json_t *tickers_array = json_object_get(feed, "ticker_sentiment");
        if (!json_is_array(tickers_array))
        {
            perror("Error when reading object array");
            log_it("Error when reading object array");
            json_decref(root_news);
            return 317;
        }



        char *tickers = (char *) calloc(13, sizeof(char)); /*initially give it a size of 15 as tickers cannot have more than 5
        + coma + space + null terminator letters P.S. Had to add possibility for CRYPTO:BTC */
        for (int j = 0; j < json_array_size(tickers_array); j++)
        {
            /* since the tickers can be more than one, we have to iterate over the entire array 
            and add them onto a single string*/
            json_t *current_ticker = json_array_get(tickers_array, j);
            if (!json_is_object(current_ticker))
            {
                perror("Error when readng object array");
                log_it("Error when readng object array");
                json_decref(root_news);
                return 318;
            }
            

            // create temporary ticker that will be added to the tickers char to have a long char with all possible tickers
            json_t *temp_ticker_json = json_object_get(current_ticker, "ticker");
            if (!json_is_string(temp_ticker_json))
            {
                perror("Error when reading object array");
                log_it("Error when reading object array");
                json_decref(root_news);
                return 319;
            }
            const char *temp_ticker = json_string_value(temp_ticker_json);


            
            if (!j && json_array_size(feed) == 1){

                // if it is the first ticker and the array is only one length
                strcpy(tickers, temp_ticker);
                break;
            }
            else if (!j)
            // if it is the first ticker, then we have to copy it into the tickers char AND that the array is not just one length
            {
                strcpy(tickers, temp_ticker);
                strcat(tickers, ", ");
            }
            else
            {
                tickers = realloc(tickers, sizeof(tickers) + 12);
                if (!tickers)
                {
                    perror("Unable to allocate memory");
                    log_it("Unable to allocate memory");
                    return 320;
                }
                strcat(tickers, ", ");
                strcat(tickers, temp_ticker); 
            } 
            
        }
        sentiments[i].tickers = strdup(tickers);
        if(tickers) free(tickers);

    }
    return 0;
}
