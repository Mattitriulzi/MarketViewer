#include "interface.hpp"

QDockWidget *dock = nullptr;

void setMiddleDock(QListWidget *listWidget);

QStackedWidget *activeStack = nullptr;

QPropertyAnimation *dockSize = nullptr;

void toggleDockVisibility();

int createSideBar(QMainWindow *mainwindow)
{
    log_it("Creating Sidebar");

    dock = new (std::nothrow) QDockWidget(mainwindow);
    check(dock, 920);
    dock->setTitleBarWidget(new (std::nothrow) QWidget());

    QListWidget *list = new (std::nothrow) QListWidget(dock);
    check(list, 921);
    list->setMinimumWidth(0);
    list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Add the options to the list
    QListWidgetItem *stockItem = new (std::nothrow) QListWidgetItem("Stocks");
    check(stockItem, 930);

    QListWidgetItem *newsItem = new (std::nothrow) QListWidgetItem("News");
    check(newsItem, 931);

    QListWidgetItem *forexItem = new (std::nothrow) QListWidgetItem("Forex");
    check(forexItem, 9311);

    QListWidgetItem *cryptoItem = new (std::nothrow) QListWidgetItem("Crypto");
    check(cryptoItem, 9312);

    stockItem->setTextAlignment(Qt::AlignCenter);
    stockItem->setForeground(QBrush(QColor("#dcd6f7")));

    newsItem->setForeground(QBrush(QColor("#dcd6f7")));
    newsItem->setTextAlignment(Qt::AlignCenter);

    forexItem->setForeground(QBrush(QColor("#dcd6f7")));
    forexItem->setTextAlignment(Qt::AlignCenter);

    cryptoItem->setForeground(QBrush(QColor("#dcd6f7")));
    cryptoItem->setTextAlignment(Qt::AlignCenter);
    
    list->addItem(stockItem);
    list->addItem(forexItem);
    list->addItem(cryptoItem);
    list->addItem(newsItem);

    list->setStyleSheet("QListWidget {background: transparent; border: 0}");

    setMiddleDock(list);

    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    dock->setVisible(false);

    mainwindow->addDockWidget(Qt::LeftDockWidgetArea, dock);

    log_it("Added SideBar onto main window");

    QPushButton *toggleDock = new (std::nothrow) QPushButton();
    check(toggleDock, 922);

    QIcon sidebarIcon("../sidebar.png");
    toggleDock->setIcon(sidebarIcon);
    toggleDock->setIconSize(QSize(23, 23));

    toggleDock->setStyleSheet("QPushButton { background-color : #eeeeee; border-radius: 5px}"
                                "QPushButton:hover { background-color: #dcd6f7; }"
                                "QPushButton:pressed { background-color: #a8a2b1; }");
    toggleDock->setFixedSize(30, 30);

    dockSize = new (std::nothrow) QPropertyAnimation(dock, "maximumWidth");
    // Pre-load Animation to make it smoother
    dockSize->setDuration(700);
    dockSize->setStartValue(0);
    dockSize->setEndValue(0);
    dockSize->start();

    QObject::connect(toggleDock, &QPushButton::clicked, toggleDockVisibility);
    
    layout->addWidget(toggleDock, 0, 0);

    // Create a Stack with all of the widgets that there are to display
    QStackedWidget *choiceStack = new (std::nothrow) QStackedWidget;
    check(choiceStack, 923);

    choiceStack->addWidget(stockWidget);
    choiceStack->addWidget(forexWidget);
    choiceStack->addWidget(cryptoWidget);
    choiceStack->addWidget(newsWidget);
    
    

    QStackedWidget *allWidgets[4] = {stockWidget, forexWidget, cryptoWidget, newsWidget};
    
    activeStack = allWidgets[0];    


    // Connect the clicking of an item in the sidebar list to changing the content being shown
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

    // Buttons to modify the current Stack
    // + Horizontal layout to place the buttons

    QHBoxLayout *buttonLayout = new (std::nothrow) QHBoxLayout();
    check(buttonLayout, 930);


    QPushButton *next = new (std::nothrow) QPushButton();
    check(next, 924);
    next->setMinimumSize(20, 20);
    next->setMaximumSize(50, 50);
    next->setStyleSheet("QPushButton { background-color : #eeeeee; border-radius: 5px; text-align: center}"
                        "QPushButton:hover { background-color: #dcd6f7; }"
                        "QPushButton:pressed { background-color: #a8a2b1; }");

    QIcon nextIcon("../arrowRight.png");
    next->setIcon(nextIcon);
    next->setIconSize(QSize(21, 21));

    QPushButton *previous = new (std::nothrow) QPushButton();
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

    QGraphicsDropShadowEffect *shadow = new (std::nothrow) QGraphicsDropShadowEffect;
    check(shadow, 926);
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
    QWidget *widget = new (std::nothrow) QWidget();
    QVBoxLayout *dockLayout = new (std::nothrow) QVBoxLayout(widget);

    if (!widget || !dockLayout) perror("Unable to allocate memory");

    dock->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                    "stop:0 #660033, stop:1 #8A2BE2);");

    dockLayout->addStretch();

    dockLayout->addWidget(listWidget);

    dockLayout->addStretch();

    dock->setWidget(widget);
}


void toggleDockVisibility()
{
    static const QRect wantedGeom = QRect(0, 0, 250, 500);


    dock->setMinimumWidth(0);


    if (dock->isVisible()) {
        QObject::connect(dockSize, &QPropertyAnimation::finished, []() {
            dock->setVisible(false);
        });

        dockSize->setStartValue(dock->maximumWidth());
        dockSize->setEndValue(0);
    } else if (!dock->isVisible()) {
        QObject::disconnect(dockSize, &QPropertyAnimation::finished, nullptr, nullptr);

        dock->setVisible(true);
        dockSize->setStartValue(0);

        dockSize->setEndValue(wantedGeom.width());
    }
    dockSize->start();
}
