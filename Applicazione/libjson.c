#include "stock.h"
#define buffer_len 4096

char *read_file(FILE *file, int length);

/*temporary files were created in the header file, respectively stock_data_active and stock_data_sentiment*/
/*structs were created in the header, respectively (stock) active_stocks and (news) sentiments*/

int json(void)
{

    char *json_active = read_file(stock_data_active, buffer_len);
    char *json_news = read_file(stock_data_sentiment, buffer_len);
    if (json_active == NULL || json_news == NULL)
    {
        perror("Unable to read files");
        return 6;
    }


    // load the json strings via jansson
    json_error_t *error;
    json_t *root_active = json_loads(json_active, 0, &error);
    json_t *root_news = json_loads(json_news, 0, &error);
    if (!root_active || !root_news)
    {
        perror("Unable to load json string");
        fprintf(stderr, "%d : %s", error.line, error.text);
        return 7;
    }
    free(json_active);
    free(json_news);

    // check if data is object
    if (!json_is_object(root_active) || !json_is_object(root_news))
    {
        perror("Root is not an object");
        json_decref(root_active);
        json_decref(root_news);
        return 8;
    }








    // check if what the object contains is an array
    json_t *most_active = json_array_get(root_active, "most_actively_traded");
    if (!json_is_array(most_active))
    {
        perror("Root object is not an array");
        json_decref(most_active);
        json_decref(root_active);
        return 9;
    }
    // array of stock structs is declared in the header file "stock.h"
    active_stocks = (stock *) calloc(LENGTH_STOCKS, sizeof(stock));
    // iterate over the object array and store the data inside our arrays of stock
    
    for (int i = 0; json_array_size(most_active); i++)
    {
        /*read the array, array contains objects (key value pairs) that must be read (with already known keys) and then stored into
        the predisposed structs, there are 20 most_active stocks theoretically ordered in their activity in the API
        Error checking checks if each pair is a string(already known type) and if not then has to print error and free both the array 
        and the original object*/
        const char *ticker, *price, *price_change, *change_percentage, *volume;


        ticker = json_string_value(json_object_get(most_active, "ticker"));
        if (!json_is_string((active_stocks + i)->ticker))
        {
            perror("Error when reading object array");
            json_decref(most_active);
            json_decref(root_active);
            free(ticker);
            return 10;
        }
        (active_stocks + i)->ticker = strdup(ticker);


        price = json_string_value(json_object_get(most_active, "price"));
        if (!json_is_string((active_stocks + i)->price))
        {
            perror("Error when reading object array");
            json_decref(most_active);
            json_decref(root_active);
            return 10;
        }
        (active_stocks + i)->price = strdup(price);


        price_change = json_string_value(json_object_get(most_active, "change_amount"));
        if (!json_is_string((active_stocks + i)->price_change))
        {
            perror("Error when reading object array");
            json_decref(most_active);
            json_decref(root_active);
            return 10;
        }
        (active_stocks + i)->price_change = strdup(price_change)


        change_percentage = json_string_value(json_object_get(most_active, "change_percentage"))
        if (!json_is_string((active_stocks + i)->change_percentage))
        {
            perror("Error when reading object array");
            json_decref(most_active);
            json_decref(root_active);
            return 10;
        }
        (active_stocks + i)->change_percentage = strdup(change_percentage);


        volume = json_string_value(json_object_get(most_active, "volume"));
        if (!json_is_string((active_stocks + i)->volume))
        {
            perror("Error when reading object array");
            json_decref(most_active);
            json_decref(root_active);
            return 10;
        }
        (active_stocks + i)->volume = strdup(volume);
    }
    /*freeing all the variables used until now, leaving only the struct with all the values needed*/
    free(ticker);
    free(price);
    free(price_change);
    free(change_percentage);
    free(volume);
    json_decref(most_active);
    json_decref(root_active);






    // news sentiment struct is declared in the header file.
    sentiments = (news *) calloc(LENGTH_NEWS, sizeof(news));


    /*Time to star the deloading for the news json file, first we will extract the array containing the news and then
    take what interests us */
    json_t *feed = json_array_get(root_news, "feed"); // extract the feed from the json giant object
    if (!json_is_array(feed))
    {
        perror("Feed is not an object");
        json_decref(feed);
        json_decref(root_news);
        return 11;
    }

    for (int i = 0; i < LENGTH_NEWS; i++)
    {
        char *title, *url, *summary, *sentiment, *tickers;


        title = json_string_value(json_object_get(feed, "title"));
        if (!json_is_string(title))
        {
            perror("Error when reading object array");
            json_decref(feed);
            json_decref(root_news);
            return 11;
        }
        (sentiments + i)->title = strdup(title);


        url = json_string_value(json_object_get(feed, "url"));
        if(!json_is_string(url))
        {
            perror("Error when reading object array");
            json_decref(feed);
            json_decref(root_news);
            return 11;
        }
        (sentiments + i)->url = strdup(url);


        summary = json_string_value(json_object_get(feed,"summary"));
        if(!json_is_string(summary))
        {
            perror("Error when reading object array");
            json_decref(feed);
            json_decref(root_news);
            return 11;
        }
        (sentiments + i)->summary = strdup(summary)


        sentiment = json_string_value(json_object_get(feed, "overall_sentiment_label"));
        if(!json_is_string(sentiment))
        {
            perror("Error when reading object array");
            json_decref(feed);
            json_decref(root_news);
            return 11;
        }
        (sentiments + i)->sentiment = strdup(sentiment);

        json_t *tickers_array = json_get_array(feed, "tickers_sentiment")
        if (!json_is_array(tickers_array))
        {
            perror("Error when reading object array");
            jeson_decref(feed);
            json_decref(root_news);
            return 12;
        }


        tickers = (char *) calloc(8, sizeof(char)); // initially give it a size of 8 as tickers cannot have more than 5
        // + coma + space + null terminator letters
        for (int j = 0; j < json_array_size(tickers_array); j++)
        {
            // create temporary ticker that will be added to the tickers char to have a long char with all possible tickers
            char *temp_ticker = json_string_value(json_get_object(tickers_array, "ticker"));
            if (!json_is_string(temp_ticker))
            {
                perror("Error when reading object array");
                json_decref(tickers_array);
                json_decref(feed);
                json_decref(root_news);
                return 12;
            }
            strcat(temp_ticker, ", ");
            if (!j)
                strcpy(tickers, temp_tickers);
            else
            {
                tickers = realloc(tickers, (strlen(tickers) + strlen(temp_ticker)) * sizeof(char) );
                if (tickers == NULL)
                {
                    perror("Unable to allocate memory");
                    return 12;
                }

                strcat(tickers, temp_ticker); 
            } 
            (sentiments + i)->tickers = strdup(tickers);
        }
    }
    /*freeing all variables*/
    free(title);
    free(url);
    free(summary);
    free(sentiment);
    free(tickers);
    json_decref(tickers_array);
    json_decref(feed);
    json_decref(root_news);
    
    fclose(stock_data_active);
    fclose(stock_data_sentiment);
}











char *read_file(FILE *file, int length)
{
    char *s = (char *) calloc(length + 1, sizeof(char));
    if (!s)
    {
        perror("Unable to allocate memory");
        return NULL;
    }
    char *buffer = (char *) calloc(length + 1, sizeof(char));
    if (!s)
    {
        perror("Unable to allocate memory");
        return NULL;
    }
    int n = 0; // number of iterations

    if(!(char *buffer = (char *) calloc()) {
        perror("Unable to allocate")
    }

    size_t read;
    while ((read = fread(&buffer, sizeof(char), length, file)) > 0)
    {
        *(buffer + read) = '\0';
        if (!n)
        {
            strcpy(s, buffer);
        }
        else 
        {
            s = (char *)realloc(s, (strlen(s) +  strlen(buffer)) * sizeof(char));
            if (!s)
            {
                perror("Unable to allocate memory");
                return NULL;
            }
            strcat(s, buffer);
        }
        n++;
    }
    free(buffer);
    return s;
}