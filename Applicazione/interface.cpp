#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>

int interface(void)
{
    //creating the application and its main window
    int argc = 1;
    char *argv[] = {"", NULL };
    QApplication app(argc,argv);
    QMainWindow mainwindow;
    mainwindow->resize(1500, 1000);

    //create a central widget to hold the layout
    QWidget *centralwidget = new QWidget(&mainwindow);

    /*Create a QGridLayout for the variables
    It should have probably 2 columns, one for stock information
    and one for news information, one column each*/
    QGridLayout *layout = new QGridLayout(centralwidget);

    /*sentiments[0 -> 9]
    active_stocks[0 -> 19]
    these are the two struct variables holding all information*/
 
    QString ticker;
    for (int i = 0; i < LENGTH_STOCKS; i++)
    // iterate through the struct news array to concatenate all information
    {
        ticker += QString("%1 \n %2 \n %3 \n %4 \n %5 \n\n").arg(active_stocks[i].ticker).arg(active_stocks[i].price)
        .arg(active_stocks[i].price_change).arg(active_stocks[i].change_percentage).arg(active_stocks[i].volume);
    }
    QString news;
    for (int i = 0; i < LENGTH_NEWS; i++)
    // iterate through the struct news array to concatenate all information
    {
        news += QString("%1 \n %2 \n %3 \n %4 \n %5 \n\n").arg(sentiments[i].title).arg(sentiments[i].URL)
        .arg(sentiments[i].summary).arg(sentiments[i].sentiment).arg(sentiments[i].tickers);
    }

    // initiate label + scroll area
   QLabel *stock_info = new QLabel(ticker);
   QLabel *news_info = new QLabel(news);
   QScrollArea *scroll_stock = new QScrollArea;
   QScrollArea *scroll_news = new QScrollArea;

   //set the labels as scrollable
   scroll_stock->setWidget(stock_info);
   scroll_news->setWidget(news_info);

   //add the scroll areas to the layout
   layout->addWidget(scroll_stock, 0, 0);
   layout->addWidget(scroll_news, 0, 1);

   mainwindow.setCentralWidget(centralwidget);

   mainwindow.show();



    // starting the app loop
    return app.exec();
}
