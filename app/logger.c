#include "stock.h"
#include <time.h>
/*This function will log all of the apps operations inside a log.txt to be able 
to check in the future for any errors

Function will need a message to be written into the log file
It will then automatically fetch the time and date of the operation, write 
the message inside the file and then close it.

The log_it function will need to be called after every major operation

for now major operations are:
- Fetching data
- JSON files being successfully loaded into objects
- the objects being succesfully parsed and put into two different structs
- Successfull creation of the database and initialisation of the tables
(- and if the database already exists, the successful opening of the database)
- date being successfully checked to avoid duplicates
- the data being successfully written into the database
- successful close of the dabatase
- successful close and removal of the files
- successful freeing of everythng that needs to be freed
- the creation of the interface through cpp
- the successful close of the interface

any errors will also be output precisely inside the log.txt file to allow for 
easy debugging

*/

void log_it(const char *msg) {
    // int i is there as a flag if it is the beginning or end of program to prind newlines



    // open file
    FILE *log_file = fopen("logs.txt", "a");
    if (!log_file) {
        perror("Unable to create or open log file");
        return;
    }

    // case where it is the beginning of the file
    if (!msg) {
        fprintf(log_file, "\n\n");
        fclose(log_file);
        return;
    }


    // get the current time
    time_t seconds = time(NULL);
    struct tm *time = localtime(&seconds);
    if (!time) {
        perror("Unable to get time");
        fclose(log_file);
        return;
    }
    
    // read the struct time and format a string with the time template
    char date[23];
    strftime(date, sizeof(date), "[%Y-%m-%d %H:%M:%S]", time); 

    // print the time and message to the log file
    fprintf(log_file, "%s %s\n", date, msg);

    // close the file
    
    fclose(log_file);
        
    return;

}