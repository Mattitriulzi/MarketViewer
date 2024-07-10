#include "stock.h"


int json_parse_sentiment(json_t *root_news)
{
        /*Time to star the deloading for the news json file, first we will extract the array containing the news and then
    take what interests us */
    json_t *feed_array = json_object_get(root_news, "feed"); // extract the feed from the json giant object
    if (!json_is_array(feed_array))
    {
        log_it("Feed is not an object");
        json_decref(root_news);
        return 5000;
    }

    char *tickers;


    for (int i = 0; i < LENGTH_NEWS; i++)
    {
        const char *title, *url, *summary, *sentiment; // tickers is a special case, hence will initialise later
        json_t *feed = json_array_get(feed_array, i);
        if (!json_is_object(feed))
        {
            log_it("Error when reading object array");
            json_decref(root_news);
            return 5001;
        }


        json_t *title_json = json_object_get(feed, "title");
        if (!json_is_string(title_json))
        {
            log_it("Error when reading object array");
            json_decref(root_news);
            return 5002;
        }


        json_t *url_json = json_object_get(feed, "url");
        if(!json_is_string(url_json))
        {
            log_it("Error when reading object array");
            json_decref(root_news);
            return 5003;
        }


        json_t *summary_json = json_object_get(feed, "summary");
        if(!json_is_string(summary_json))
        {
            log_it("Error when reading object array");
            json_decref(root_news);
            return 5004;
        }


        json_t *sentiment_json = json_object_get(feed, "overall_sentiment_label");
        if(!json_is_string(sentiment_json))
        {
            log_it("Error when reading object array");
            json_decref(root_news);
            return 5005;
        }


        json_t *tickers_array = json_object_get(feed, "ticker_sentiment");
        if (!json_is_array(tickers_array))
        {
            log_it("Error when reading object array");
            json_decref(root_news);
            return 5006;
        }



        tickers = (char *) calloc(15, sizeof(char)); /*initially give it a size of 15 as tickers cannot have more than 5
        + coma + space + null terminator letters P.S. Had to add possibility for CRYPTO:BTC */
        for (int j = 0; j < json_array_size(tickers_array); j++)
        {
            /* since the tickers can be more than one, we have to iterate over the entire array 
            and add them onto a single string*/
            json_t *current_ticker = json_array_get(tickers_array, j);
            if (!json_is_object(current_ticker))
            {
                log_it("Error when readng object array");
                json_decref(root_news);
                return 5007;
            }
            

            // create temporary ticker that will be added to the tickers char to have a long char with all possible tickers
            json_t *temp_ticker_json = json_object_get(current_ticker, "ticker");
            if (!json_is_string(temp_ticker_json))
            {
                log_it("Error when reading object array");
                json_decref(root_news);
                return 5008;
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
            }
            else
            {
                tickers = realloc(tickers, strlen(tickers) + 15);
                if (!tickers)
                {
                    perror("Unable to allocate memory");
                    log_it("Unable to allocate memory");
                    return 5009;
                }
                strcat(tickers, ", ");
                strcat(tickers, temp_ticker); 
            } 
            
        }


        sentiments[i].title = strdup(json_string_value(title_json));
        check(sentiments[i].title, 5010);
        sentiments[i].URL = strdup(json_string_value(url_json));
        check(sentiments[i].URL, 5011);
        sentiments[i].summary = strdup(json_string_value(summary_json));
        check(sentiments[i].summary, 5012);
        sentiments[i].sentiment = strdup(json_string_value(sentiment_json));
        check(sentiments[i].sentiment, 5013);
        sentiments[i].tickers = strdup(tickers);
        check(sentiments[i].tickers, 5014);
        
    }
    if (tickers) free(tickers);
    return 0;
}
