#include <iostream>
#include <QApplication>
#include <QmainWindow>

int main()
{
    int argc = 1;
    char *argv[] = {"Test", NULL };
    QApplication app(argc,argv);
    QMainWindow mainwindow;
    mainwindow.show();

    return app.exec();
}
