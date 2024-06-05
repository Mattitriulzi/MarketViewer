#include "stock.h"

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
- successful close and removal of the files
- successful freeing of everythng that needs to be freed
- the creation of the interface through cpp
- the successful close of the interface

any errors will also be output precisely inside the log.txt file to allow for 
easy debugging

*/
int log_it(char *msg)
{
    
}