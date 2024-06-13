#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#ifdef __cplusplus
extern "C" {
#endif 
#include "stock.h"
#ifdef __cplusplus
}
#endif

// https://doc.qt.io/qt-6/qtdoc-demos-documentviewer-example.html



int interface(void)
{
    //creating the application and its main window
    int argc = 1;
    char *argv[] = {strdup("StockFetch"), NULL};
    QApplication app(argc,argv);
    QMainWindow mainwindow;

    //create a central widget to hold the layout
    QWidget *centralwidget = new QWidget(&mainwindow);

    /*Create a QGridLayout for the variables
    It should have probably 2 columns, one for stock information
    and one for news information, one column each*/
    QGridLayout *layout = new QGridLayout(centralwidget);

    /*sentiments[0 -> 9]
    active_stocks[0 -> 19]
    these are the two struct variables holding all information*/
 
    log_it("Successfully created Main App Window");

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
   QLabel *news_info = new QLabel(news);
   QScrollArea *scroll_stock = new QScrollArea;
   QScrollArea *scroll_news = new QScrollArea;

   log_it("Successfully created the labels and scroll areas");

   //Put the labels inside of the scrollable are
   scroll_stock->setWidget(stock_info);
   scroll_news->setWidget(news_info);

   //add the scroll areas to the layout
   layout->addWidget(scroll_stock, 0, 0);
   layout->addWidget(scroll_news, 0, 1);

   mainwindow.setCentralWidget(centralwidget);

   mainwindow.show();

    log_it("Successfully added the scroll areas to the layout");
    log_it("Successfully started Application GUI");

    // starting the app loop
    int execution = app.exec();

    if (argv[0]){
        free(argv[0]);
        argv[0] = NULL;
    }
    return execution;
}
