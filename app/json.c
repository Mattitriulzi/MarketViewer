#include "stock.h"

news sentiments[LENGTH_NEWS];

stock active_stocks[LENGTH_STOCKS];

char *date = NULL;

int fdelete(const char* filename[], unsigned arraylen);


/*temporary files were created in the header file, respectively stock_data_active and stock_data_sentiment*/
/*structs were created in the header, respectively (stock) active_stocks and (news) sentiments*/

int json(void)
{
    int error_return;
    const char *filename[] = {"stock_data_active.json", "stock_data_sentiment.json"};
    unsigned arraylen = 2;
    // load the json strings via jansson, aka create objects for each file
    json_error_t error;
    json_t *root_active = json_loadf(stock_data_active, 0, &error);
    json_t *root_news = json_loadf(stock_data_sentiment, 0, &error);
    if (!root_active || !root_news)
    {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        perror("Unable to load json string");
        log_it("Unable to load json string");
        return 301;
    }

    // time to delete the temporary files!
    log_it("Successfully loaded the json files, closing files");
    fclose(stock_data_active);
    fclose(stock_data_sentiment);
    error_return = fdelete(filename, arraylen);
    if (error_return){
        perror("Unable to delete file");
        log_it("Unable to delete file");
        return 301;
    }
    log_it("Successfully deleted the temporary files"); 
    

    log_it("Successfully closed temporary files");

    // check if data is object
    if (!json_is_object(root_active) || !json_is_object(root_news))
    {
        perror("Root is not an object");
        log_it("Root is not an object");
        json_decref(root_active);
        json_decref(root_news);
        return 302;
    }



    json_t *last_updated_json = json_object_get(root_active, "last_updated");
    // Get the date so that we are able to avoid duplications
    if (!(json_is_string(last_updated_json)))
    {
        perror("Error when reading json file");
        log_it("Error when reading json file");
        return 303;
    }
    log_it("Successfully opened json objects");

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
    if (last_updated_json) {
        json_decref(last_updated_json);
        last_updated_json = NULL;
    }

    log_it("Successfully read the date");





    error_return = json_parse_active(root_active);
    if (error_return){
        perror("Error when parsing active stocks json");
        log_it("Error when parsing active stocks json");
        return 330;
    }
    
    log_it("Successfully loaded the Active Stocks structure array");



    error_return = json_parse_sentiment(root_news);
    if (error_return){
        perror("Error when parsing news sentiment json");
        log_it("Error when parsing news sentiment json");
        return 331;
    }
    

    log_it("Successfully loaded the News sentiments structure array");

    /*freeing*/
    if (root_active) {
        json_decref(root_active);
        root_active = NULL;
    }

    if (root_news) {
        json_decref(root_news);
        root_news = NULL;
    }

    //fclose(stock_data_active);
    //fclose(stock_data_sentiment);

    log_it("Successfully freed the json objects");
    return 0;
}


int fdelete(const char* filename[], unsigned arraylen){

    for(int i = 0; i < arraylen; i++){
        if (remove(filename[i])){
            perror("Unable to delete file");
            log_it("Unable to delete file");
            return 1;
        }
    }
    return 0;
}
