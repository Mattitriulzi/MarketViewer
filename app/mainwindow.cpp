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
    centralwidget->setStyleSheet("QWidget {background: transparent; border: 0}");


    layout = new QGridLayout(centralwidget);
    check(layout, 902);

    stockWidget = new QStackedWidget();
    check(stockWidget, 911);

    newsWidget = new QStackedWidget();
    check(newsWidget, 912);
    

    log_it("Getting the Data from the structure arrays");

    QString active;
    QLabel *tempActiveLabel[LENGTH_STOCKS];
    QHBoxLayout *activeLabel[LENGTH_STOCKS];
    for (int i = 0; i < LENGTH_STOCKS; i++) {
        active = QString("Ticker: %1 \n Price: %2 \n Price Change: %3 \n Change Percentage: %4 \n Volume: %5 \n\n")
        .arg(active_stocks[i].ticker).arg(active_stocks[i].price)
        .arg(active_stocks[i].price_change).arg(active_stocks[i].change_percentage)
        .arg(active_stocks[i].volume);

        // create Label and change its color
        tempActiveLabel[i] = new QLabel(active);
        check(tempActiveLabel[i], 903);
        tempActiveLabel[i]->setStyleSheet("QLabel { color : #dcd6f7; border : 2px solid black; border-radius : 20px}");
        tempActiveLabel[i]->setAlignment(Qt::AlignCenter);
        tempActiveLabel[i]->setMaximumWidth(270);
        tempActiveLabel[i]->setMaximumHeight(270);
        tempActiveLabel[i]->setContentsMargins(2,2,2,2);

        activeLabel[i] = new QHBoxLayout();
        check(activeLabel[i], 903);
        activelabel[i]->addStretch(1);
        activeLabel[i]->addWidget(tempActiveLabel[i]);
        activeLabel[i]->addStretch();


        stockWidget->addLayout(activeLabel[i]);
    }

    stockWidget->setStyleSheet("QWidget { background:transparent; border : 0}");

    QString news;
    QScrollArea *newsLabel[LENGTH_NEWS];
    QLabel *tempNewsLabel[LENGTH_NEWS];
    for (int i = 0; i < LENGTH_NEWS; i++) {
        news = QString("Title: %1 \n URL: %2 \n Summary: %3 \n Sentiment: %4 \n Tickers: %5 \n\n")
        .arg(sentiments[i].title).arg(sentiments[i].URL)
        .arg(sentiments[i].summary).arg(sentiments[i].sentiment).arg(sentiments[i].tickers);

        tempNewsLabel[i] = new QLabel(news);
        check(tempNewsLabel[i], 904);
        tempNewsLabel[i]->setStyleSheet("QLabel { background:transparent;color : #dcd6f7; border: 0}");
        tempNewsLabel[i]->setAlignment(Qt::AlignCenter);

        newsLabel[i] = new QScrollArea;
        check(newsLabel[i], 905);
        newsLabel[i]->setWidget(tempNewsLabel[i]);
        newsLabel[i]->setAlignment(Qt::AlignCenter);
        newsLabel[i]->setStyleSheet(" QScrollArea {background: transparent; border: 0}"
                                    "QScrollBar:horizontal { "
                                    "border: none; "
                                    "background: transparent; "
                                    "width:  15px; " 
                                    "height: 15px"
                                    "}"
                                    "QScrollBar::handle:horizontal {"
                                    "background: grey;"
                                    "border-radius : 7px;"
                                    "min-width: 15px;"
                                    "max-width: 15px"
                                    "}" 
                                    "QScrollBar::add-line:horizontal{"
                                    "border: none;"
                                    "background: none;"
                                    "width: 0px; "
                                    "height: 0px"
                                    "}"
                                    "QScrollBar::sub-line:horizontal{"
                                    "border: none;"
                                    "background: none;"
                                    "width: 0px; "
                                    "height: 0px"
                                    "}");

        newsWidget->addWidget(newsLabel[i]);
    }

    log_it("All data found");

    mainwindow->setCentralWidget(centralwidget);


    log_it("MainWindow succcessfully created");

    return 0;
}