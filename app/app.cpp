#include "interface.hpp"


// https://doc.qt.io/qt-6/qtdoc-demos-documentviewer-example.html

#define VERSION "v2.2-beta"




int app(void)
{
    log_it("Starting the GUI creation process");
    //creating the application and its main window
    int argc = 1;
    char *argv[] = {(char *) "StockFetch"};
    QApplication app(argc,argv);
    QCoreApplication::setApplicationName("Stocks Viewer");
    QCoreApplication::setApplicationVersion(VERSION);
    QMainWindow mainwindow;
    mainwindow.resize(1640, 980);
    QString title = QString("Stocks Viewer - Version %1")
                    .arg(QCoreApplication::applicationVersion());
    mainwindow.setWindowTitle(title);

    log_it("Start the Widget Creation process");

    int error = createScrollAreas(&mainwindow);
    if (error) {
        perror("Unable to create Mainwindow");
        log_it("Unable to create MainWindow");
        return 1000;
    }

    log_it("Widgets created");

    log_it("Start the SideBar creation process");

    error = createSideBar(&mainwindow);
    if (error) {
        perror("Unable to create Sidebar");
        log_it("Unable to create SideBar");
        return 1001;
    }

    log_it("SideBar created");
    
    log_it("Successfully started Application GUI");



    mainwindow.setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, \
     stop:0 #0f0c29, stop:0.5 #302b63, stop:1 #24243e);");
    mainwindow.show();
    // starting the app loop
    int execution = app.exec();

    return execution;
}
