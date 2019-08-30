#ifndef MAPQML_H
#define MAPQML_H

#include <QWidget>
#include <QFrame>
#include <QBoxLayout>
#include <QQuickView>
#include <QGraphicsDropShadowEffect>
#include <QAction>
#include <QFont>

enum MapType
{
    ArcGIS,
    OSM
};

class MapQML : public QWidget
{
    Q_OBJECT
public:
    explicit MapQML(QAction * action, QWidget *parent = nullptr);
    ~MapQML();
    void CreateMap(QAction * action);
    void CreateFrame();
    void CreateShadow();
    void CreateFont();

    QFrame * GetFrame();
    QGraphicsDropShadowEffect * GetShadow();

signals:

public slots:
    void Change(QAction * action);

private:
    QQuickView * map;
    QFrame * frame;
    QWidget * widget;
    QBoxLayout * layout;
    QGraphicsDropShadowEffect * shadow;
    MapType type;
    QFont font;
};

#endif // MAPQML_H
