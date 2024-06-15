#include "interface.hpp"

QDockWidget *dock = NULL;

void setMiddleDock(QListWidget *listWidget);

int createSideBar(QMainWindow *mainwindow)
{
    log_it("Creating Sidebar");

    dock = new QDockWidget(mainwindow);
    check(dock, 920);
    dock->setTitleBarWidget(new QWidget());

    QListWidget *list = new QListWidget(dock);
    check(list, 921);

    //Add the options to the list
    QListWidgetItem *stockItem = new QListWidgetItem("Stocks");
    check(stockItem, 930);

    QListWidgetItem *newsItem = new QListWidgetItem("News");
    check(newsItem, 931);

    stockItem->setTextAlignment(Qt::AlignCenter);
    stockItem->setForeground(QBrush(QColor("#dcd6f7")));
    newsItem->setForeground(QBrush(QColor("#dcd6f7")));
    newsItem->setTextAlignment(Qt::AlignCenter);

    list->addItem(stockItem);
    list->addItem(newsItem);
    //list->addItem("Crypto");
    //list->addItem("Forex");

    setMiddleDock(list);

    log_it("SideBar created");

    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    mainwindow->addDockWidget(Qt::LeftDockWidgetArea, dock);

    log_it("Added SideBar onto main window");

    QPushButton *toggleDock = new QPushButton();
    check(toggleDock, 922);

    QIcon sidebarIcon("../sidebar.png");
    toggleDock->setIcon(sidebarIcon);
    toggleDock->setIconSize(QSize(20, 20));

    toggleDock->setStyleSheet("QPushButton { background-color : #eeeeee; border-radius: 5px}");
    toggleDock->setFixedSize(25, 25);

    // Connect the Button click to hide/show the Sidebar, with animation
    /*QPropertyAnimation *animation = new QPropertyAnimation(dock, "geometry");
    check(animation, 940);
    animation->setDuration(1000)*/
    
    QObject::connect(toggleDock, &QPushButton::clicked, []() {
        dock->setVisible(!dock->isVisible());
    });
    
    layout->addWidget(toggleDock, 0, 0);

    // create a Stack with all of the widgets that there are to display
    QStackedWidget *choiceStack = new QStackedWidget;
    check(choiceStack, 923);

    choiceStack->addWidget(stockWidget);
    choiceStack->addWidget(newsWidget);
    //stackedWidget->addWidget(cryptoWidget);
    //StackedWidget->addWidget(forexWidget);

    // connect the clicking of an item in the sidebar list to changing the content being shown
    QObject::connect(list, &QListWidget::currentItemChanged,
    [choiceStack] (QListWidgetItem *current, QListWidgetItem *previous) {
        if (current) {
            choiceStack->setCurrentIndex(current->listWidget()->row(current));
        }
    });
    // listWidget is a method of QListWidgetItem that returns a pointer to the QListWidget the item belongs to.

    layout->addWidget(choiceStack, 1, 0);

    
    return 0;
}


void setMiddleDock(QListWidget *listWidget)
{
    QWidget *widget = new QWidget();
    QVBoxLayout *dockLayout = new QVBoxLayout(widget);

    if (!widget || !dockLayout) perror("Unable to allocate memory");
    

    dockLayout->addStretch();

    dockLayout->addWidget(listWidget);

    dockLayout->addStretch();

    dock->setWidget(widget);

}