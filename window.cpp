#include "window.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    Settings();
    CreateButton();
    CreateToolBar();
}


Window::~Window()
{
    delete dummy1;
    delete dummy2;
    delete text;
    delete addqmlButton;
    delete addcppButton;
    delete changeButton;
    delete toolBar;

    DeleteMapCPP();
    DeleteMapQML();
    DeleteDock();
}


void Window::Settings()
{
    QPalette pal;
    pal.setColor(QPalette::Background, QColor(255,255,255));
    setPalette(pal);

    setContentsMargins(20,20,20,20);
    setStyleSheet("QMainWindow::separator{ width: 20px; height: 20px; }");
    setDockOptions(DockOption::AllowNestedDocks | DockOption::AllowTabbedDocks | DockOption::AnimatedDocks);
}


void Window::CreateButton()
{
    addqmlButton = new QToolButton;
    addcppButton = new QToolButton;
    changeButton = new QToolButton;

    addqmlPix.load(":/new/Icons/addqml.png");
    addcppPix.load(":/new/Icons/addcpp.png");
    changePix.load(":/new/Icons/change.png");

    addqmlButton->setIcon(addqmlPix);
    addqmlButton->setFixedSize(60,60);

    addcppButton->setIcon(addcppPix);
    addqmlButton->setFixedSize(60,60);

    changeButton->setIcon(changePix);
    changeButton->setFixedSize(60,60);
}


void Window::CreateToolBar()
{
    toolBar = new QToolBar;
    toolBar->setStyleSheet("background-color: gray; margin: 3px 3px");

    QFont font("Helvetica[Cronyx]", 50);
    font.setBold(true);

    text = new QAction;
    text->setText("");
    text->setFont(font);

    dummy1 = new QWidget(this);
    dummy2 = new QWidget(this);

    dummy1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    dummy2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    toolBar->addWidget(dummy1);
    toolBar->addWidget(addqmlButton);
    toolBar->addWidget(addcppButton);
    toolBar->addWidget(changeButton);
    toolBar->addAction(text);
    toolBar->addWidget(dummy2);
    toolBar->setIconSize(QSize(54,54));
    toolBar->setFixedHeight(72);
    addToolBar(Qt::TopToolBarArea, toolBar);

    connect(addqmlButton, &QPushButton::clicked, [this]() { AddQMLMap(text); });
    connect(addcppButton, SIGNAL(clicked()), this, SLOT(AddCPPMap()));
}


void Window::AddQMLMap(QAction * action)
{
    auto dock = new QDockWidget(tr("MapQML"), this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);

    auto map = new MapQML(action);
    dock->setWidget(map->GetFrame());
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setGraphicsEffect(map->GetShadow());

    connect(changeButton, &QPushButton::clicked, [map, this]() { map->Change(text); });

    dockWidget_v.push_back(dock);
    mapQML_v.push_back(map);
}


void Window::AddCPPMap()
{
    auto dock = new QDockWidget(tr("MapCPP"), this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);

    auto map = new MapCPP;
    dock->setWidget(map->GetFrame());
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setGraphicsEffect(map->GetShadow());

    connect(map->GetButton(), &QPushButton::clicked, [map]() { map->ToggleShadow();});

    dockWidget_v.push_back(dock);
    mapCPP_v.push_back(map);
}


void Window::DeleteDock()
{
    foreach(auto dock, dockWidget_v)
        delete dock;
}


void Window::DeleteMapQML()
{
    foreach(auto map, mapQML_v)
        delete map;
}


void Window::DeleteMapCPP()
{
    foreach(auto map, mapCPP_v)
        delete map;
}
