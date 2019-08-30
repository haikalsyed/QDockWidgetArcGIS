#ifndef MAPCPP_H
#define MAPCPP_H

#include <QWidget>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QGridLayout>
#include <QDockWidget>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>

#include "Map.h"
#include "MapGraphicsView.h"

namespace Esri
{
    namespace ArcGISRuntime
    {
        class Map;
        class MapGraphicsView;
    }
}

enum Shadowing
{
    OFF,
    ON
};

class MapCPP : public QWidget
{
    Q_OBJECT
public:
    explicit MapCPP(QWidget *parent = nullptr);
    ~MapCPP();

    void CreateShadow();
    void CreateFrame();
    void CreateMap();
    void CreateButton();
    void CreateMessage();

    QFrame * GetFrame();
    QGraphicsDropShadowEffect * GetShadow();
    QPushButton * GetButton();

signals:

public slots:
    void ToggleShadow();

private:
    Esri::ArcGISRuntime::Map * map;
    Esri::ArcGISRuntime::MapGraphicsView * widget;
    QFrame * frame;
    QGridLayout * layout;
    QPushButton * button;
    QGraphicsDropShadowEffect * shadow;
    Shadowing shadowing;
};

#endif // MAPCPP_H
