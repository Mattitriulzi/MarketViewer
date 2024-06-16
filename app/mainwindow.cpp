#include "interface.hpp"

QStackedWidget *stockWidget = NULL;

QStackedWidget *newsWidget = NULL;

QGridLayout *layout = NULL;

int createMainWindow(QMainWindow *mainwindow)
{

    log_it("Successfully created Main Window");

    log_it("Beginning to create Widgets");

    check(mainwindow, 900);

    QWidget *centralwidget = new QWidget(mainwindow);
    check(centralwidget, 901);

    layout = new QGridLayout(centralwidget);
    check(layout, 902);

    stockWidget = new QStackedWidget();
    check(stockWidget, 911);

    newsWidget = new QStackedWidget();
    check(newsWidget, 912);

    log_it("Getting the Data from the structure arrays");

    QString active;
    QLabel *activeLabel[LENGTH_STOCKS];
    for (int i = 0; i < LENGTH_STOCKS; i++) {
        active = QString("Ticker: %1 \n Price: %2 \n Price Change: %3 \n Change Percentage: %4 \n Volume: %5 \n\n")
        .arg(active_stocks[i].ticker).arg(active_stocks[i].price)
        .arg(active_stocks[i].price_change).arg(active_stocks[i].change_percentage)
        .arg(active_stocks[i].volume);

        // create Label and change its color
        activeLabel[i] = new QLabel(active);
        check(activeLabel[i], 903);
        activeLabel[i]->setStyleSheet("QLabel { color : #dcd6f7}");


        stockWidget->addWidget(activeLabel[i]);

    }

    QString news;
    QScrollArea *newsLabel[LENGTH_NEWS];
    QLabel *tempLabel[LENGTH_NEWS];
    for (int i = 0; i < LENGTH_NEWS; i++) {
        news = QString("Title: %1 \n URL: %2 \n Summary: %3 \n Sentiment: %4 \n Tickers: %5 \n\n")
        .arg(sentiments[i].title).arg(sentiments[i].URL)
        .arg(sentiments[i].summary).arg(sentiments[i].sentiment).arg(sentiments[i].tickers);

        tempLabel[i] = new QLabel(news);
        check(tempLabel[i], 904);
        tempLabel[i]->setStyleSheet("QLabel { color : #dcd6f7}");

        newsLabel[i] = new QScrollArea;
        check(newsLabel[i], 905);
        newsLabel[i]->setWidget(tempLabel[i]);

        newsWidget->addWidget(newsLabel[i]);
    }

    log_it("All data found");

    mainwindow->setCentralWidget(centralwidget);


    log_it("MainWindow succcessfully created");

    return 0;
}