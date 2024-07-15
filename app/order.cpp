#include "interface.hpp"
#include <mach-o/dyld.h>
#include <limits.h>
#include <libgen.h>



int main(void)
{   
    char buf[PATH_MAX];
    uint32_t bufsize = (uint32_t) PATH_MAX;
    if (_NSGetExecutablePath(buf, &bufsize)){
        return 1;
    }
    
    char *dir = dirname(buf);

    if (chdir(dir)) {
        return 2;
    }
 
    // order of which functions to perform
    log_it("Test LogFile Length");
    if (!FIRST_TIME_FLAG)
        log_it(NULL);
    log_it("---------------------------------------------------");
    log_it(" ");
    log_it("(MAIN) Starting Application");

    int err;
    err = Stock_Data(); 
    if(err)
    {
        log_it(int_to_char(err));
        log_it(strerror(errno)); // Replaced errnum with errno
        log_it("(MAIN) Error when fetching Stock Data, exiting");
        return 1011; 
    }
    log_it("(MAIN) Successfully fetched Stock Data");


    log_it(" ");


    log_it("(MAIN) Starting json file parsing");
    err = json(); 
    if (err)
    {
        log_it(int_to_char(err));
        log_it(strerror(errno)); // Replaced errnum with errno
        log_it("(MAIN) Error when parsing json file, exiting");
        return 1011; 
    }
    log_it("(MAIN) Successfully parsed json file");


    log_it(" ");


    log_it("(MAIN) Checking the database's existence");
    err = SQL(); 
    if(err)
    {
        log_it(int_to_char(err));
        log_it(strerror(errno)); // Replaced errnum with errno
        log_it("(MAIN) Error when creating SQL database, exiting");
        return 1011; 
    }
    log_it("(MAIN) Successfully created SQL database");


    log_it(" ");


    log_it("(MAIN) Starting database update process");
    err = SQL_read(); 
    if(err)
    {
        log_it(int_to_char(err));
        log_it(strerror(errno)); // Replaced errnum with errno
        log_it("(MAIN) Error when reading SQL database, exiting");
        return 1011; 
    }
    log_it("(MAIN) Successfully updated database if necessary");


    log_it(" ");


    log_it("(MAIN) Starting Application GUI");
    err = app(); 
    if(err)
    {
        log_it(int_to_char(err));
        log_it(strerror(errno)); // Replaced errnum with errno
        log_it("(MAIN) Error when starting interface");
        return 1011; 
    }
    log_it("(MAIN) Successfully closed application GUI");


    log_it(" ");
    
    log_it("(MAIN) Starting the freeing process");
    err = free_structs();
    if (err)
    {
        log_it(int_to_char(err));
        log_it(strerror(errno)); // Replaced errnum with errno
        log_it("(MAIN) Error when freeing the structs");
        return 1011;
    }
    log_it("(MAIN) Successfully freed all structure arrays");
    log_it("(MAIN) Successfully stopped the Application");
    log_it(" ");
    log_it("---------------------------------------------------");

    return 0; 
}


char *int_to_char(int n) 
{
    //maximum error length is 1 000
    static char string[5];

    snprintf(string, sizeof(string), "%d", n);

    return string;
}

