#include "interface.hpp"


QScrollArea *stockWidget = NULL;

QScrollArea *newsWidget = NULL;

QGridLayout *layout = NULL;


int createScrollAreas(QMainWindow *mainwindow)
{
    log_it("Successfully created main window");
    log_it("Beginning to create widgets");

    check(mainwindow, 900);

    QWidget *centralWidget = new QWidget(mainwindow);
    check(centralWidget, 903);

    layout = new QGridLayout(centralWidget);
    check(layout, 904);


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
    
    QLabel *stockInfo = new QLabel(ticker);
    check(stockInfo, 903);
    stockInfo->setStyleSheet("QLabel { color : #dcd6f7}");

    QLabel *newsInfo = new QLabel(news);
    check(newsInfo, 904);
    newsInfo->setStyleSheet("QLabel { color : #dcd6f7}");

    //create two scrollable areas for each Tab Page
    stockWidget = new QScrollArea();
    check(stockWidget, 905);

    newsWidget = new QScrollArea();
    check(newsWidget, 906);

    //set the Labels into the Scroll Areas
    stockWidget->setWidget(stockInfo);

    newsWidget->setWidget(newsInfo);

    //set the widget for the scroll areas

    mainwindow->setCentralWidget(centralWidget);

    log_it("Set all Widgets into the main window");

    return 0;
}