#include "interface.hpp"

QStackedWidget *stockWidget = nullptr;

QStackedWidget *newsWidget = nullptr;

QGridLayout *layout = nullptr;

int createMainWindow(QMainWindow *mainwindow)
{
    log_it("Successfully created Main Window");
    log_it("Beginning to create Widgets");

    check(mainwindow, 900);

    QWidget *centralwidget = new (std::nothrow) QWidget(mainwindow);
    check(centralwidget, 901);
    centralwidget->setStyleSheet("QWidget {background: transparent; border: 0}");

    layout = new (std::nothrow) QGridLayout(centralwidget);
    check(layout, 902);

    stockWidget = new (std::nothrow) QStackedWidget();
    check(stockWidget, 911);

    newsWidget = new (std::nothrow) QStackedWidget();
    check(newsWidget, 912);

    log_it("Getting the Data from the structure arrays");

    QString active;
    QLabel *tempActiveLabel[LENGTH_STOCKS];
    QWidget *activeWidget[LENGTH_STOCKS];
    QHBoxLayout *activeLabel[LENGTH_STOCKS];
    for (int i = 0; i < LENGTH_STOCKS; i++) {
        active = QString("Ticker: %1 \n Price: %2 \n Price Change: %3 \n Change Percentage: %4 \n Volume: %5 \n\n")
        .arg(active_stocks[i].ticker).arg(active_stocks[i].price)
        .arg(active_stocks[i].price_change).arg(active_stocks[i].change_percentage)
        .arg(active_stocks[i].volume);

        tempActiveLabel[i] = new (std::nothrow) QLabel(active);
        check(tempActiveLabel[i], 903);
        tempActiveLabel[i]->setStyleSheet("QLabel { color : #000000; border : 2px solid white; border-radius : 20px;"
                                            "background: white; font-size: 22px;}" );
        tempActiveLabel[i]->setAlignment(Qt::AlignCenter);
        tempActiveLabel[i]->setMinimumWidth(450);
        tempActiveLabel[i]->setMaximumWidth(1000);
        tempActiveLabel[i]->setMinimumHeight(270);
        tempActiveLabel[i]->setMaximumHeight(450);

        activeLabel[i] = new (std::nothrow) QHBoxLayout();
        check(activeLabel[i], 903);
        activeLabel[i]->addStretch(1);
        activeLabel[i]->addWidget(tempActiveLabel[i]);
        activeLabel[i]->addStretch(1);

        activeWidget[i] = new (std::nothrow) QWidget();
        check(activeWidget[i], 903);
        activeWidget[i]->setLayout(activeLabel[i]);

        stockWidget->addWidget(activeWidget[i]);
    }

    stockWidget->setStyleSheet("QWidget { background:transparent; border : 0}");

    QString news;
    QScrollArea *newsLabel[LENGTH_NEWS];
    QLabel *tempNewsLabel[LENGTH_NEWS];
    QWidget *newWidget[LENGTH_NEWS];
    for (int i = 0; i < LENGTH_NEWS; i++) {
        news = QString("Title: %1 \n URL: %2 \n Summary: %3 \n Sentiment: %4 \n Tickers: %5 \n\n")
        .arg(sentiments[i].title).arg(sentiments[i].URL)
        .arg(sentiments[i].summary).arg(sentiments[i].sentiment).arg(sentiments[i].tickers);

        tempNewsLabel[i] = new (std::nothrow) QLabel(news);
        check(tempNewsLabel[i], 904);
        tempNewsLabel[i]->setStyleSheet("QLabel { background:transparent;color : #000000; border: 0;"
                                        " font-size: 22px;}");

        newsLabel[i] = new (std::nothrow) QScrollArea;
        check(newsLabel[i], 905);
        newsLabel[i]->setWidget(tempNewsLabel[i]);
        newsLabel[i]->setAlignment(Qt::AlignCenter);
        newsLabel[i]->setStyleSheet(" QScrollArea {background: white; border: 0; border-radius: 20px;}"
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
