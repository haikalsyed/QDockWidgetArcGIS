#include "mapqml.h"

MapQML::MapQML( QAction * action, QWidget *parent) : QWidget(parent)
{
    if(action->text() == "" || action->text() == "ArcGIS")
        type = ArcGIS;
    else
        type = OSM;
    CreateShadow();
    CreateMap(action);
    CreateFrame();
}


MapQML::~MapQML()
{
    delete shadow;
    delete map;
    delete widget;
    delete layout;
    delete frame;
}


void MapQML::CreateMap(QAction * action)
{
    map = new QQuickView;
    map->setResizeMode(map->SizeRootObjectToView);
    if(type == ArcGIS)
    {
        map->setSource(QUrl::fromLocalFile("C:/Users/Administrator/Documents/MapLoader/Map.qml"));
        action->setText("ArcGIS");
    }

    else
    {
        map->setSource(QUrl::fromLocalFile("C:/Users/Administrator/Documents/MapLoader/OSMMap.qml"));
        action->setText("OSM");
    }

    widget = new QWidget;
    widget =  QWidget::createWindowContainer(map);
}


void MapQML::CreateFrame()
{
    layout = new QBoxLayout(QBoxLayout::TopToBottom);
    layout->addWidget(widget);

    frame = new QFrame();
    frame->setFrameStyle(QFrame::StyledPanel);
    frame->setStyleSheet("background-color :  rgb(231, 232, 236); border : 0px ");
    frame->setLayout(layout);
}


void MapQML::CreateShadow()
{
    shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(5);
    shadow->setXOffset(10);
    shadow->setYOffset(10);
    shadow->setColor(Qt::black);
}


QFrame * MapQML::GetFrame()
{
    return frame;
}


QGraphicsDropShadowEffect * MapQML::GetShadow()
{
    return shadow;
}


void MapQML::Change(QAction * action)
{
    if(type == ArcGIS)
    {
        action->setText("OSM");
        map->setSource(QUrl::fromLocalFile("C:/Users/Administrator/Documents/MapLoader/OSMMap.qml"));
        type = OSM;
    }
    else if(type == OSM)
    {
        action->setText("ArcGIS");
        map->setSource(QUrl::fromLocalFile("C:/Users/Administrator/Documents/MapLoader/Map.qml"));
        type = ArcGIS;
    }
}
