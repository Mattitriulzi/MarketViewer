#include "interface.hpp"

#define log_errnum(errnum) do{if(errnum) log_it(int_to_char(errnum));}while(0);

// https://doc.qt.io/qt-6/qtdoc-demos-documentviewer-example.html
// https://github.com/KDE/labplot/commit/3ef13eed12d03ca6f4026f4217b986010096e597
// https://doc.qt.io/qt-5/stylesheet-reference.html

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
    mainwindow.resize(900, 500 );

    int fontId = QFontDatabase::addApplicationFont(QString("../Resources/spaceGrotesk.ttf"));
    if (fontId == -1) 
        log_it("Failed to load font Space Grotesk, default system font will be used");
    else log_it("Font: Space Grotesk, other fonts may be available in the future ;)");
    
    QFont defaultFont("Space Grotesk", 16);
    
    QApplication::setFont(defaultFont);


    QString title = QString("Stocks Viewer %1")
                    .arg(QCoreApplication::applicationVersion());
    mainwindow.setWindowTitle(title);

    log_it("Start the Widget Creation process");

    int error = createMainWindow(&mainwindow);
    if (error) {
        log_errnum(error);
        log_it("Unable to create MainWindow");
        return 9000;
    }

    log_it("Widgets created");

    log_it("Start the SideBar creation process");

    error = createSideBar(&mainwindow);
    if (error) {
        log_errnum(error);
        log_it("Unable to create SideBar");
        return 9001;
    }
    
    log_it("Successfully started Application GUI");



    mainwindow.setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, \
     stop:0 #0f0c29, stop:0.5 #302b63, stop:1 #24243e);");
    mainwindow.show();

    // starting the app loop
    return app.exec();
}
