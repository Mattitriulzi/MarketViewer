#include "stock.h"

news sentiments[LENGTH_NEWS];

stock active_stocks[LENGTH_STOCKS];

currencies exchangeRates[numCurrencies];

char *date = NULL;

int fdelete(const char* filePath[], unsigned arraylen);

int freeRoots(json_t *allRoots[], int arrayLen);

/*temporary files were created in the header file, respectively stock_data_active and stock_data_sentiment*/
/*structs were created in the header, respectively (stock) active_stocks and (news) sentiments*/

int json(void)
{  
    int error_return;
    // load the json strings via jansson, aka create objects for each file
    json_error_t error;

    json_t *allRoots[NUM_FILES];

    for (int i = 0; i < NUM_FILES; i++) {
	    allRoots[i] = json_loadf(allFilePointers[i], 0, &error);
	    if (!allRoots[i]) {
		    log_it("Unable to load json file");
		    return 300;
	    }
    }

    // time to delete the temporary files!
    log_it("Successfully loaded the json files, closing files");
    /*for (int i = 0; i < NUM_FILES; i ++) 
	    fclose(allFilePointers[i]);
    error_return = fdelete(filePaths, NUM_FILES);
    if (error_return) {
        log_it("Unable to delete file");
        return 301;
    }*/
  
    log_it("Successfully deleted the temporary files");

    log_it("Verifying loaded json data");
    for (int i = 0; i < NUM_FILES; i++) {
	    if (!json_is_object(allRoots[i])) {
            log_it("Root is not an object");
            freeRoots(allRoots, NUM_FILES);
            return 302;
        }
    }
    log_it("Data seems valid");

    log_it("Getting the date needed to check for duplicate insertions in database");

    json_t *lastUpdatedJson = json_object_get(allRoots[ACTIVE], "last_updated");
    if (!json_is_string(lastUpdatedJson)) {
        log_it("Error when fetching date");
        return 303;
    }
    
    log_it("Successfully got date");

    const char *lastUpdated = json_string_value(lastUpdatedJson);
    /*Read the last_updated string to be able to check for the first space and keep
    only the date rather than the whole string, this is the format:
    "last_updated": "2024-05-22 16:15:59 US/Eastern"
    We wish to keep only the date. However we have to first copy the string into another 
    variable as this one is a constant*/ 
    date = strdup(lastUpdated);
    for (int i = 0; i < strlen(date); i ++) {
        if (*date == ' ') {
            *date = '\0';
            break;
        }
    }

    if (lastUpdatedJson)   
        json_decref(lastUpdatedJson);

    log_it("Successfully saved the date");

    log_it("Starting the Active Tickers loading process");

    error_return = json_parse_active(allRoots[ACTIVE]);
    if (error_return) {
        log_it("Error when parsing Active Tickers JSON");
        return 310;
    }

    log_it("Successfully loaded the Active Tickers");

    log_it("Starting the News Sentiments loading process");

    error_return = json_parse_sentiment(allRoots[NEWS]);
    if (error_return) {
        log_it("Error when parsing News JSON");
        return 311;
    }

    log_it("Successfully loaded the News");

    log_it("Starting the ForEX and Crypto loading process");

    for (int i = 2; i < NUM_FILES; i++) {
        error_return = parseCurrencies(allRoots[i], i - 2); 
        // since i is the total number of files and the currencies start at 2, just remove 2 to
        // get the current currency count (or pair) 
        if (error_return) {
            log_it("Error when parsing Currencies JSON");
            freeRoots(allRoots, NUM_FILES);
            printf("Error is %d", error_return);
            return 312;
        }
    }
    
    log_it("Successfully loaded the ForEX and Crypto");


    
    error_return = freeRoots(allRoots, NUM_FILES);
    if (error_return) {
        log_it("Error when trying to free JSON Roots");
        return 330;
    }
    return 0;
}


int fdelete(const char* filePath[], unsigned arraylen)
{

    for(int i = 0; i < arraylen; i++){
        if (remove(filePath[i])){
            perror("Unable to delete file");
            log_it("Unable to delete file");
            return 1;
        }
    }
    return 0;
}


int freeRoots(json_t *allRoots[], int arrayLen)
{
    for (int i = 0; i < arrayLen; i++) {
        if (allRoots[i]) {
            json_decref(allRoots[i]);
            allRoots[i] = NULL;
        }
    }
    return 0;
}

