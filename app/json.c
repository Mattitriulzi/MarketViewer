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
    for (int i = 0; i < NUM_FILES; i ++) 
	    fclose(allFilePointers[i]);
    /*error_return = fdelete(filePaths, NUM_FILES);
    if (error_return) {
        log_it("Unable to delete file");
        return 301;
    }*/
  
    log_it("Successfully closed temporary files");
    log_it("Successfully deleted the temporary files");

    log_it("Verifying loaded json data");

    return 0;
}
