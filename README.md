# App 

This app gets the latest news and the current most active stocks and prints it on an interface. 

It allows (me) to avoid having to actually look it up on the internet. 

**CURRENTLY ONLY WORKS ON ARM64 MACS**

# Implementation

This app is made fully in C (backend) and C++ (frontend, only 1 file).

The following libraries were used:

libcurl\
jansson \
QT(C++)  
sqlite3 

# History-Keeping

The news and active stocks are added into an sqlite database. The date is checked to avoid duplicated entries. 

It is therefore possible to access the database using sqlite3 in the terminal to fetch historical data.

# Possible features in the future
**Buttons on the interface to access the sqlite database, allowing for fast history keeping**
        
   *ex: button that asks for a date, news or stocks and prints all that info*
    
**Better-looking interface** \
**possibly more requests on the API**
**Crypto Information**
**Forex Information**
        
