#include "interface.hpp"


// https://doc.qt.io/qt-6/qtdoc-demos-documentviewer-example.html

#define VERSION "v2.2-beta"




int interface(void)
{
    log_it("Starting the GUI creation process");
    //creating the application and its main window
    int argc = 1;
    char *argv[] = {(char *) "StockFetch"};
    QApplication app(argc,argv);
    QCoreApplication::setApplicationName("Stocks Viewer");
    QCoreApplication::setApplicationVersion(VERSION);
    QMainWindow mainwindow;

    int error = createScrollAreas(&mainwindow);
    if (error){
        perror("Unable to create Mainwindow");
        log_it("Unable to create MainWindow");
        return 1000;
    }
    
    log_it("Successfully started Application GUI");

    // starting the app loop
    unsigned execution = app.exec();

    return execution;
}
