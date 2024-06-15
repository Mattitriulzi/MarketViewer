#include <QApplication>
#include <QCoreApplication>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include <QTabWidget>
#include <QDockWidget>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QPropertyAnimation>

int createScrollAreas(QMainWindow *mainwindow);

int createSideBar(QMainWindow *mainwindow);

extern QScrollArea *stockWidget;

extern QScrollArea *newsWidget;

extern QDockWidget *dock;

extern QGridLayout *layout;

#ifdef __cplusplus
extern "C" {
#endif 
#include "stock.h"
#ifdef __cplusplus
}
#endif
