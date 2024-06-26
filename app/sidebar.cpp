#include "interface.hpp"

QDockWidget *dock = NULL;

void setMiddleDock(QListWidget *listWidget);

QStackedWidget *activeStack = NULL;

int visibleDock = 1;

void toggleDockVisibility();

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

    list->setStyleSheet("QListWidget {background: transparent; border: 0}");

    setMiddleDock(list);

    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    dock->setVisible(1);

    mainwindow->addDockWidget(Qt::LeftDockWidgetArea, dock);

    log_it("Added SideBar onto main window");

    QPushButton *toggleDock = new QPushButton();
    check(toggleDock, 922);

    QIcon sidebarIcon("../sidebar.png");
    toggleDock->setIcon(sidebarIcon);
    toggleDock->setIconSize(QSize(23, 23));

    toggleDock->setStyleSheet("QPushButton { background-color : #eeeeee; border-radius: 5px}"
                                "QPushButton:hover { background-color: #dcd6f7; }"
                                "QPushButton:pressed { background-color: #a8a2b1; }");
    toggleDock->setFixedSize(30, 30);

    QObject::connect(toggleDock, &QPushButton::clicked, toggleDockVisibility);

    /*QObject::connect(toggleDock, &QPushButton::clicked, []() {
        dock->setVisible(!dock->isVisible());
    });*/
    
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

    

    QPushButton *next = new QPushButton();
    check(next, 924);
    next->setMinimumSize(20, 20);
    next->setMaximumSize(50, 50);
    next->setStyleSheet("QPushButton { background-color : #eeeeee; border-radius: 5px; text-align: center}"
                        "QPushButton:hover { background-color: #dcd6f7; }"
                        "QPushButton:pressed { background-color: #a8a2b1; }");

    QIcon nextIcon("../arrowRight.png");
    next->setIcon(nextIcon);
    next->setIconSize(QSize(21, 21));

    QPushButton *previous = new QPushButton();
    check(previous, 925);
    previous->setMinimumSize(25, 25);
    previous->setMaximumSize(50, 50);
    previous->setStyleSheet("QPushButton { background-color : #eeeeee; border-radius: 5px; text-align: center; }"
                            "QPushButton:hover { background-color: #dcd6f7; }"
                            "QPushButton:pressed { background-color: #a8a2b1; }");

    QIcon previousIcon("../arrowLeft.png");
    previous->setIcon(previousIcon);
    previous->setIconSize(QSize(21, 21));

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

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(3);
    shadow->setOffset(5, 5);

    next->setGraphicsEffect(shadow);
    previous->setGraphicsEffect(shadow);
    toggleDock->setGraphicsEffect(shadow);

    layout->addLayout(buttonLayout, 2, 0);

    
    return 0;
}


void setMiddleDock(QListWidget *listWidget)
{
    QWidget *widget = new QWidget();
    QVBoxLayout *dockLayout = new QVBoxLayout(widget);

    if (!widget || !dockLayout) perror("Unable to allocate memory");

    dock->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                    "stop:0 #FFD1DC, stop:1 #8A2BE2);");

    dockLayout->addStretch();

    dockLayout->addWidget(listWidget);

    dockLayout->addStretch();

    dock->setWidget(widget);
}


void toggleDockVisibility()
{
    if (!dock) return;

    //create an opacity effect to be able to make the dock "transparent"
    static QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(dock);
    if (!opacityEffect) return;
    dock->setGraphicsEffect(opacityEffect);

    //create an animation to animate the dock's closing/opening
    static QPropertyAnimation *dockEffect = new QPropertyAnimation(dock, "geometry");
    if (!dockEffect) return;
    dockEffect->setDuration(750);

    static const QRect dockGeometry = dock->geometry();

    QObject::disconnect(dockEffect, &QPropertyAnimation::finished, nullptr, nullptr);

    //global variable visibleDock is used to keep track of the dock's visibility
    if (dock->isVisible()) {
        // Animate to a geometry with 0 width and 0 height to hide
        
        QObject::connect(dockEffect, &QPropertyAnimation::finished, []() {
            dock->setVisible(0);
            opacityEffect->setOpacity(0.0);
        });

        dockEffect->setStartValue(dock->geometry());
        dockEffect->setEndValue(QRect(-dockGeometry.width(), dockGeometry.y(), 0, dockGeometry.height()));
        
    } else if (!dock->isVisible()){

        dock->setVisible(1);
        // Animate back to a visible state
        dockEffect->setStartValue(QRect(-dockGeometry.width(), dockGeometry.y(), 0, dockGeometry.height()));
        dockEffect->setEndValue(dockGeometry);
        opacityEffect->setOpacity(1.0);
        
    }
    dockEffect->start();
    return;
}
