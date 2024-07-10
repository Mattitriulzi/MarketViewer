#include "interface.hpp"

#define numForexPairs 3

#define numCryptoPairs 3

QStackedWidget *stockWidget = nullptr;

QStackedWidget *newsWidget = nullptr;

QStackedWidget *forexWidget = nullptr;

QStackedWidget *cryptoWidget = nullptr;

QGridLayout *layout = nullptr;

int createMainWindow(QMainWindow *mainwindow)
{
    log_it("Successfully created Main Window");
    log_it("Beginning to create Widgets");

    check(mainwindow, 1100);

    QWidget *centralwidget = new (std::nothrow) QWidget(mainwindow);
    check(centralwidget, 1101);
    centralwidget->setStyleSheet("QWidget {background: transparent; border: 0}");

    layout = new (std::nothrow) QGridLayout(centralwidget);
    check(layout, 1102);

    stockWidget = new (std::nothrow) QStackedWidget();
    check(stockWidget, 1103);

    newsWidget = new (std::nothrow) QStackedWidget();
    check(newsWidget, 1104);

    forexWidget = new (std::nothrow) QStackedWidget();
    check(forexWidget, 1105);

    cryptoWidget = new (std::nothrow) QStackedWidget();
    check(cryptoWidget, 1106);

    log_it("Getting the Data from the structure arrays");

    QString tempString;
    QLabel *tempActiveLabel[LENGTH_STOCKS];
    QWidget *activeWidget[LENGTH_STOCKS];
    QHBoxLayout *activeLabel[LENGTH_STOCKS];
    for (int i = 0; i < LENGTH_STOCKS; i++) {
        tempString = QString("Ticker: %1 \n Price: %2 \n Price Change: %3 \n Change Percentage: %4 \n Volume: %5 \n\n")
        .arg(active_stocks[i].ticker).arg(active_stocks[i].price)
        .arg(active_stocks[i].price_change).arg(active_stocks[i].change_percentage)
        .arg(active_stocks[i].volume);

        tempActiveLabel[i] = new (std::nothrow) QLabel(tempString);
        check(tempActiveLabel[i], 1107);
        tempActiveLabel[i]->setStyleSheet("QLabel { color : #000000; border : 2px solid white; border-radius : 20px;"
                                            "background: white; font-size: 22px;}" );
        tempActiveLabel[i]->setAlignment(Qt::AlignCenter);
        tempActiveLabel[i]->setMinimumWidth(450);
        tempActiveLabel[i]->setMaximumWidth(1000);
        tempActiveLabel[i]->setMinimumHeight(270);
        tempActiveLabel[i]->setMaximumHeight(450);

        activeLabel[i] = new (std::nothrow) QHBoxLayout();
        check(activeLabel[i], 1108);
        activeLabel[i]->addStretch(1);
        activeLabel[i]->addWidget(tempActiveLabel[i]);
        activeLabel[i]->addStretch(1);

        activeWidget[i] = new (std::nothrow) QWidget();
        check(activeWidget[i], 1109);
        activeWidget[i]->setLayout(activeLabel[i]);

        stockWidget->addWidget(activeWidget[i]);
    }

    stockWidget->setStyleSheet("QWidget { background:transparent; border : 0}");

    QScrollArea *newsLabel[LENGTH_NEWS];
    QLabel *tempNewsLabel[LENGTH_NEWS];
    for (int i = 0; i < LENGTH_NEWS; i++) {
        tempString = QString("Title: %1 \n URL: %2 \n Summary: %3 \n Sentiment: %4 \n Tickers: %5 \n\n")
        .arg(sentiments[i].title).arg(sentiments[i].URL)
        .arg(sentiments[i].summary).arg(sentiments[i].sentiment).arg(sentiments[i].tickers);

        tempNewsLabel[i] = new (std::nothrow) QLabel(tempString);
        check(tempNewsLabel[i], 1110);
        tempNewsLabel[i]->setStyleSheet("QLabel { background:transparent;color : #000000; border: 0;"
                                        " font-size: 22px;}");

        newsLabel[i] = new (std::nothrow) QScrollArea;
        check(newsLabel[i], 1111);
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
    
    QLabel *tempCurrencyLabel[numForexPairs];
    QWidget *currencywidget[numForexPairs];
    QHBoxLayout *currencyLayout[numForexPairs];
    for (int i = 0; i < numForexPairs; i++) {
        tempString = QString("From: %1 \n To: %2 \n Exchange Rate: %3 \n").arg(exchangeRates[i].fromCurrency)
            .arg(exchangeRates[i].toCurrency).arg(exchangeRates[i].price);

        tempCurrencyLabel[i] = new (std::nothrow) QLabel(tempString);
        check(tempCurrencyLabel[i], 1112);
        tempCurrencyLabel[i]->setStyleSheet("QLabel { color : #000000; border : 2px solid white; border-radius : 20px;"
                                            "background: white; font-size: 22px;}" );

        tempCurrencyLabel[i]->setAlignment(Qt::AlignCenter);
        tempCurrencyLabel[i]->setMinimumWidth(450);
        tempCurrencyLabel[i]->setMaximumWidth(1000);
        tempCurrencyLabel[i]->setMinimumHeight(270);
        tempCurrencyLabel[i]->setMaximumHeight(450);

        currencyLayout[i] = new (std::nothrow) QHBoxLayout();
        check(currencyLayout[i], 1113);
        currencyLayout[i]->addStretch(1);
        currencyLayout[i]->addWidget(tempCurrencyLabel[i]);
        currencyLayout[i]->addStretch(1);

        currencywidget[i] = new (std::nothrow) QWidget();
        check(currencywidget[i], 1114);
        currencywidget[i]->setLayout(currencyLayout[i]);

        forexWidget->addWidget(currencywidget[i]);
    }

    QLabel *tempCryptoLabel[numCryptoPairs];
    QWidget *tempcryptoWidget[numCryptoPairs];
    QHBoxLayout *cryptoLayout[numCryptoPairs];
    for (int i = 0; i < numCryptoPairs; i++) {
        tempString = QString("From: %1 \n To: %2 \n Exchange Rate: %3 \n").arg(exchangeRates[i + numForexPairs].fromCurrency)
            .arg(exchangeRates[i + numForexPairs].toCurrency).arg(exchangeRates[i + numForexPairs].price);

        tempCryptoLabel[i] = new (std::nothrow) QLabel(tempString);
        check(tempCryptoLabel[i], 1115);
        tempCryptoLabel[i]->setStyleSheet("QLabel { color : #000000; border : 2px solid white; border-radius : 20px;"
                                            "background: white; font-size: 22px;}" );

        tempCryptoLabel[i]->setAlignment(Qt::AlignCenter);
        tempCryptoLabel[i]->setMinimumWidth(450);
        tempCryptoLabel[i]->setMaximumWidth(1000);
        tempCryptoLabel[i]->setMinimumHeight(270);
        tempCryptoLabel[i]->setMaximumHeight(450);

        cryptoLayout[i] = new (std::nothrow) QHBoxLayout();
        check(cryptoLayout[i], 1116);
        cryptoLayout[i]->addStretch(1);
        cryptoLayout[i]->addWidget(tempCryptoLabel[i]);
        cryptoLayout[i]->addStretch(1);

        tempcryptoWidget[i] = new (std::nothrow) QWidget();
        check(tempcryptoWidget[i], 1117);
        tempcryptoWidget[i]->setLayout(cryptoLayout[i]);

        cryptoWidget->addWidget(tempcryptoWidget[i]);
    }

    mainwindow->setCentralWidget(centralwidget);

    log_it("MainWindow successfully created");

    return 0;
}
