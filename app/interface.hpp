#include <QApplication>
#include <QCoreApplication>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QDockWidget>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPixMap>


int createMainWindow(QMainWindow *mainwindow);

int createSideBar(QMainWindow *mainwindow);

extern QStackedWidget *stockWidget;

extern QStackedWidget *newsWidget;

extern QDockWidget *dock;

extern QGridLayout *layout;

#ifdef __cplusplus
extern "C" {
#endif 
#include "stock.h"
#ifdef __cplusplus
}
#endif
