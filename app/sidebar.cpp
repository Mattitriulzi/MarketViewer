#include "interface.hpp"

QDockWidget *dock = NULL;

void setMiddleDock(QListWidget *listWidget);

void modifyActive(QStackedWidget **active, QStackedWidget *allWidgets[]);

QStackedWidget *activeStack = NULL;

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

    dock->setVisible(0);

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
    
    

    QStackedWidget *allWidgets[2] = {stockWidget, newsWidget};
    
    activeStack = allWidgets[0];    


    // connect the clicking of an item in the sidebar list to changing the content being shown
    QObject::connect(list, &QListWidget::currentItemChanged,
    [choiceStack, allWidgets] (QListWidgetItem *current, QListWidgetItem *previous) mutable {
        if (current) {
            int currentIndex = current->listWidget()->row(current);
            choiceStack->setCurrentIndex(currentIndex);
            activeStack = allWidgets[currentIndex];

        }
    });
    // listWidget is a method of QListWidgetItem that returns a pointer to the QListWidget the item belongs to.
    // currentItemChanged returns 2, but we are only interested in the current one

    layout->addWidget(choiceStack, 1, 0);

    //Buttons to modify the current Stack
    // + Horizontal layout to place the buttons

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    check(buttonLayout, 930);

    

    QPushButton *next = new QPushButton("N");
    check(next, 924);
    next->setFixedSize(25, 25);
    next->setStyleSheet("QPushButton { background-color : #eeeeee; border-radius: 5px; text-align: center}");

    QIcon nextIcon("../arrowRight.png");
    next->setIcon(nextIcon);
    next->setIconSize(QSize(20, 20));

    QPushButton *previous = new QPushButton("P");
    check(previous, 925);
    previous->setFixedSize(25, 25);
    previous->setStyleSheet("QPushButton { background-color : #eeeeee; border-radius: 5px; text-align: center; }");

    QIcon previousIcon("../arrowLeft.png");
    previous->setIcon(previousIcon);
    previous->setIconSize(QSize(20, 20));

    buttonLayout->addWidget(previous);
    buttonLayout->addWidget(next);


    QObject::connect(next, &QPushButton::clicked, []() {
            int currentIndex = activeStack->currentIndex();
            if (currentIndex < activeStack->count() - 1) {
                activeStack->setCurrentIndex(currentIndex + 1);
            }
    });

    QObject::connect(previous, &QPushButton::clicked, []() {
        int currentIndex = activeStack->currentIndex();
        if (currentIndex > 0) {
            activeStack->setCurrentIndex(currentIndex - 1);
        }
    });

    layout->addLayout(buttonLayout, 2, 0);

    
    return 0;
}


void setMiddleDock(QListWidget *listWidget)
{
    QWidget *widget = new QWidget();
    QVBoxLayout *dockLayout = new QVBoxLayout(widget);

    if (!widget || !dockLayout) perror("Unable to allocate memory");

    dock->setStyleSheet("background-color : #000000");

    dockLayout->addStretch();

    dockLayout->addWidget(listWidget);

    dockLayout->addStretch();

    dock->setWidget(widget);
}
