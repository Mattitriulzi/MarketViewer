
#include "stock.h"

news *sentiments = NULL;

stock *active_stocks = NULL;

char *date = NULL;


/*temporary files were created in the header file, respectively stock_data_active and stock_data_sentiment*/
/*structs were created in the header, respectively (stock) active_stocks and (news) sentiments*/

int json(void)
{
    // old way of first reading the files into a string and then loading them into jansson instead of directly loading them
    /*char *json_active = read_file(stock_data_active, buffer_len);
    char *json_news = read_file(stock_data_sentiment, buffer_len);
    if (json_active == NULL || json_news == NULL)
    {
        perror("Unable to read files");
        return 300;
    } */

   

    // load the json strings via jansson, aka create objects for each file
    json_error_t error;
    json_t *root_active = json_loadf(stock_data_active, 0, &error);
    json_t *root_news = json_loadf(stock_data_sentiment, 0, &error);
    if (!root_active || !root_news)
    {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        perror("Unable to load json string");
        return 301;
    }

    // check if data is object
    if (!json_is_object(root_active) || !json_is_object(root_news))
    {
        perror("Root is not an object");
        json_decref(root_active);
        json_decref(root_news);
        return 302;
    }



    json_t *last_updated_json = json_object_get(root_active, "last_updated");
    // Get the date so that we are able to avoid duplications
    if (!(json_is_string(last_updated_json)))
    {
        perror("Error when reading json file");
        return 303;
    }
    const char* last_updated = json_string_value(last_updated_json);
    /*Read the last_updated string to be able to check for the first space and keep
    only the date rather than the whole string, this is the format:
    "last_updated": "2024-05-22 16:15:59 US/Eastern"
    We wish to keep only the date. However we have to first copy the string into another 
    variable as this one is a constant*/
    date = strdup(last_updated);
    for (int i = 0; i < strlen(date); i++)
    {
        if (*(date + i) == ' ')
        {
            *(date + i) = '\0';
            break;
        }
    }
    if (last_updated_json) json_decref(last_updated_json);





    // get the most_actively_traded object and check if what the object contains is an array
    json_t *most_actively_traded = json_object_get(root_active, "most_actively_traded");
    if (!json_is_array(most_actively_traded))
    {
        perror("Root object is not an array");
        json_decref(most_actively_traded);
        json_decref(root_active);
        return 304;
    }
    // array of stock structs is declared in the header file "stock.h"
    active_stocks = (stock *) calloc(LENGTH_STOCKS, sizeof(stock));
    if (!active_stocks)
    {
        perror("Unable to allocate memory");
        return 320;
    }
    // iterate over the object array and store the data inside our arrays of stock
    
    for (int i = 0; i < json_array_size(most_actively_traded); i++)
    {
        /*read the array, array contains objects (key value pairs) that must be read (with already known keys) and then stored into
        the predisposed structs, there are 20 most_active stocks theoretically ordered in their activity in the API
        Error checking checks if each pair is a string(already known type) and if not then has to print error and free both the array 
        and the original object*/
        const char *ticker, *price, *price_change, *change_percentage, *volume;

        json_t* most_active = json_array_get(most_actively_traded, i);
        if (!json_is_object(most_active))
        {
            perror("Error when reading object array");
            json_decref(most_actively_traded);
            return 305;
        }




        json_t *ticker_json = json_object_get(most_active, "ticker");
        if (!json_is_string((ticker_json)))
        {
            perror("Error when reading object array");
            json_decref(root_active);
            return 306;
        }
        ticker = json_string_value(json_object_get(most_active, "ticker"));
        (active_stocks + i)->ticker = strdup(ticker);


        json_t *price_json = json_object_get(most_active, "price");
        if (!json_is_string(price_json))
        {
            perror("Error when reading object array");
            json_decref(root_active);
            return 307;
        }
        price = json_string_value(price_json);
        (active_stocks + i)->price = strdup(price);


        json_t *price_change_json = json_object_get(most_active, "change_amount");
        if (!json_is_string(price_change_json))
        {
            perror("Error when reading object array");
            json_decref(root_active);
            return 308;
        }
        price_change = json_string_value(price_change_json);
        (active_stocks + i)->price_change = strdup(price_change);


        json_t *change_percentage_json = json_object_get(most_active, "change_percentage");
        if (!json_is_string(change_percentage_json))
        {
            perror("Error when reading object array");
            json_decref(root_active);
            return 309;
        }
        change_percentage = json_string_value(change_percentage_json);
        (active_stocks + i)->change_percentage = strdup(change_percentage);


        json_t *volume_json = json_object_get(most_active, "volume");
        if (!json_is_string(volume_json))
        {
            perror("Error when reading object array");
            json_decref(root_active);
            return 310;
        }
        volume = json_string_value(volume_json);
        (active_stocks + i)->volume = strdup(volume);
    /*free(ticker);
    free(price);
    free(price_change);
    free(change_percentage);
    free(volume);
    json_decref(most_active); */
    }
    /*freeing all the variables used until now, leaving only the struct with all the values needed*/
    
    if (root_active) json_decref(root_active);



    // news sentiment struct is declared in the header file.
    sentiments = (news *) calloc(LENGTH_NEWS, sizeof(news));
    if (!sentiments)
    {
        perror("Unable to allocate memory");
        return 320;
    }


    /*Time to star the deloading for the news json file, first we will extract the array containing the news and then
    take what interests us */
    json_t *feed_array = json_object_get(root_news, "feed"); // extract the feed from the json giant object
    if (!json_is_array(feed_array))
    {
        perror("Feed is not an object");
        json_decref(root_news);
        return 311;
    }

    for (int i = 0; i < LENGTH_NEWS; i++)
    {
        const char *title, *url, *summary, *sentiment; // tickers is a special case, hence will initialise later
        json_t *feed = json_array_get(feed_array, i);
        if (!json_is_object(feed))
        {
            perror("Error when reading object array");
            json_decref(root_news);
            return 312;
        }


        json_t *title_json = json_object_get(feed, "title");
        if (!json_is_string(title_json))
        {
            perror("Error when reading object array");
            json_decref(root_news);
            return 313;
        }
        title = json_string_value(title_json);
        (sentiments + i)->title = strdup(title);


        json_t *url_json = json_object_get(feed, "url");
        if(!json_is_string(url_json))
        {
            perror("Error when reading object array");
            json_decref(root_news);
            return 314;
        }
        url = json_string_value(url_json);
        (sentiments + i)->URL = strdup(url);


        json_t *summary_json = json_object_get(feed, "summary");
        if(!json_is_string(summary_json))
        {
            perror("Error when reading object array");
            json_decref(root_news);
            return 315;
        }
        summary = json_string_value(summary_json);
        (sentiments + i)->summary = strdup(summary);


        json_t *sentiment_json = json_object_get(feed, "overall_sentiment_label");
        if(!json_is_string(sentiment_json))
        {
            perror("Error when reading object array");
            json_decref(root_news);
            return 316;
        }
        sentiment = json_string_value(sentiment_json);
        (sentiments + i)->sentiment = strdup(sentiment);


        json_t *tickers_array = json_object_get(feed, "ticker_sentiment");
        if (!json_is_array(tickers_array))
        {
            perror("Error when reading object array");
            json_decref(root_news);
            return 317;
        }


        char *tickers = (char *) calloc(12, sizeof(char)); /*initially give it a size of 12 as tickers cannot have more than 5
         + coma + space + null terminator letters P.S. Had to add possibility for CRYPTO:BTC */
        for (int j = 0; j < json_array_size(tickers_array); j++)
        {
            /* since the tickers can be more than one, we have to iterate over the entire array 
            and add them onto a single string*/
            json_t *current_ticker = json_array_get(tickers_array, j);
            if (!json_is_object(current_ticker))
            {
                perror("Error when readng object array");
                json_decref(root_news);
                return 318;
            }
            



            // create temporary ticker that will be added to the tickers char to have a long char with all possible tickers
            json_t *temp_ticker_json = json_object_get(current_ticker, "ticker");
            if (!json_is_string(temp_ticker_json))
            {
                perror("Error when reading object array");
                json_decref(root_news);
                return 319;
            }
            const char *temp_ticker = json_string_value(temp_ticker_json);




            if (!j)
            // if it is the first ticker, then we have to copy it into the tickers char
            {
                strcpy(tickers, temp_ticker);
                strcat(tickers, ", ");
            }
            else
            {
                tickers = realloc(tickers, (strlen(tickers) + strlen(temp_ticker)) * sizeof(char) + 2 );
                if (!tickers)
                {
                    perror("Unable to allocate memory");
                    return 320;
                }
                
                strcat(tickers, temp_ticker); 
            } 
            (sentiments + i)->tickers = strdup(tickers);
        }
        //free(title);
    /*free(url);
    free(summary);
    free(sentiment);
    free(tickers);
    json_decref(tickers_array);
    json_decref(feed); */
    }
    /*freeing all variables*/

    if (root_news) json_decref(root_news);
    fclose(stock_data_active);
    fclose(stock_data_sentiment);

    // delete the two files that were created
    /*
    const char *filename[] = {"stock_data_active.json", "stock_data_sentiment.json"};
    for (int i = 0; i < 2; i++){
        if (!remove(filename[i]))
        {
            perror("Unable to remove file");
            return 321;
        }
    } */
    return 0;
}


