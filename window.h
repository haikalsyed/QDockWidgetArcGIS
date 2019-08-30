#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QToolBar>
#include <QDebug>
#include <QVector>
#include <QAction>
#include <QToolButton>
#include <QPixmap>
#include <QPalette>
#include <QAction>
#include <QFont>

#include "mapqml.h"
#include "mapcpp.h"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
    void Settings();
    void CreateToolBar();
    void CreateButton();

    void DeleteDock();
    void DeleteMapQML();
    void DeleteMapCPP();

signals:

public slots:
    void AddQMLMap(QAction * action);
    void AddCPPMap();

private:
    QVector <QDockWidget *> dockWidget_v;
    QVector <MapQML *> mapQML_v;
    QVector <MapCPP *> mapCPP_v;

    QToolBar * toolBar;

    QToolButton * addqmlButton;
    QToolButton * addcppButton;
    QToolButton * changeButton;

    QPixmap addqmlPix;
    QPixmap addcppPix;
    QPixmap changePix;

    QWidget * dummy1;
    QWidget * dummy2;

    QAction * text;

};

#endif // WINDOW_H
