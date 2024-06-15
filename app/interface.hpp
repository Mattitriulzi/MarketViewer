#include <QApplication>
#include <QCoreApplication>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include <QTabWidget>


#ifdef __cplusplus
extern "C" {
#endif 
#include "stock.h"
#ifdef __cplusplus
}
#endif

#define VERSION "v2.2-beta"

int createScrollAreas(QMainWindow *mainwindow);
