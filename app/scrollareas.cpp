#include "interface.hpp"



int createScrollAreas(QMainWindow *mainwindow)
{
    check(mainwindow, 900);
    //create a central widget to hold the layout
    QWidget *centralwidget = new QWidget(mainwindow);
    check(centralwidget, 901);

    /*Create a QGridLayout for the variables
    It should have probably 2 columns, one for stock information
    and one for news information, one column each*/
    QGridLayout *layout = new QGridLayout(centralwidget);
    check(layout, 902);

    /*sentiments[0 -> 9]
    active_stocks[0 -> 19]
    these are the two struct variables holding all information*/
 
    log_it("Successfully created Main App Window");

    log_it("Fetching the data to add to QLabel");
    QString ticker;
    for (int i = 0; i < LENGTH_STOCKS; i++)
    // iterate through the struct news array to concatenate all information
    {
        ticker += QString("Ticker: %1 \n Price: %2 \n Price Change: %3 \n Change Percentage: %4 \n Volume: %5 \n\n")
        .arg(active_stocks[i].ticker).arg(active_stocks[i].price)
        .arg(active_stocks[i].price_change).arg(active_stocks[i].change_percentage)
        .arg(active_stocks[i].volume);
    }
    QString news;
    for (int i = 0; i < LENGTH_NEWS; i++)
    // iterate through the struct news array to concatenate all information
    {
        news += QString("Title: %1 \n URL: %2 \n Summary: %3 \n Sentiment: %4 \n Tickers: %5 \n\n")
        .arg(sentiments[i].title).arg(sentiments[i].URL)
        .arg(sentiments[i].summary).arg(sentiments[i].sentiment).arg(sentiments[i].tickers);
    }

    log_it("Successfully concatenated all information into a QString");

    // Initiate the two different labels and then create two scrollable areas
   QLabel *stock_info = new QLabel(ticker);
   check(stock_info, 903);
   QLabel *news_info = new QLabel(news);
   check(news_info, 904);
   QScrollArea *scroll_stock = new QScrollArea;
   check(scroll_stock, 905);
   QScrollArea *scroll_news = new QScrollArea;
   check(scroll_news, 906);

   log_it("Successfully created the labels and scroll areas");

   //Put the labels inside of the scrollable are
   scroll_stock->setWidget(stock_info);
   scroll_news->setWidget(news_info);

   //add the scroll areas to the layout
   layout->addWidget(scroll_stock, 0, 0);
   layout->addWidget(scroll_news, 0, 1);

   mainwindow->setCentralWidget(centralwidget);

   mainwindow->show();
   
   return 0;
}