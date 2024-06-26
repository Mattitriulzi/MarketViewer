#include <QApplication>
#include <QCoreApplication>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QDockWidget>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QFontDatabase>
#include <QFont>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QRect>

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
