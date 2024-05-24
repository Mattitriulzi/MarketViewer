#include <iostream>
#include <QApplication>
#include <QmainWindow>

int interface(void)
{
    int argc = 1;
    char *argv[] = {"Test", NULL };
    QApplication app(argc,argv);
    QMainWindow mainwindow;
    mainwindow.show();

    return app.exec();
}
