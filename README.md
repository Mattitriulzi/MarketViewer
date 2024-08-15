**Before judging, this app was made by a 16 year old with only basic C knowledge**

# App 

This app gets the latest news, the last day's most active stocks, the main CHF forex pairs, and the three main crypto pairs. 

It allows (me) to avoid having to actually look it up on the internet. 

# Implementation

This app is made in C and C++, the C part is all of the backend while the C++ part is the frontend

The following libraries were used:

libcurl,

jansson,

QT(C++)

sqlite3 

# History-Keeping

The news and active stocks are added into an sqlite database. The date is checked to avoid duplicated entries. 

It is therefore possible to access the database using sqlite3 in the terminal to fetch historical data.

# Possible features in the future
**Buttons on the interface to access the sqlite database, allowing for fast history keeping**
        
   *ex: button that asks for a date, news or stocks and prints all that info*

**Will not be updated any further**




        
