#include "mapcpp.h"

using namespace Esri::ArcGISRuntime;

MapCPP::MapCPP(QWidget *parent) : QWidget(parent)
{
    CreateShadow();
    CreateButton();
    CreateMap();
    CreateFrame();
}


MapCPP::~MapCPP()
{
    delete shadow;
    delete button;
    delete map;
    delete widget;
    delete layout;
    delete frame;
}


void MapCPP::CreateShadow()
{
    shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(50);
    shadow->setXOffset(10);
    shadow->setYOffset(10);
    shadow->setColor(Qt::black);
    shadow->setEnabled(false);
}


void MapCPP::CreateMessage()
{
    QMessageBox::StandardButton response;

    response = QMessageBox::question(this, "", "Do you want shadows?", QMessageBox::Yes | QMessageBox::No);

    if(response == QMessageBox::Yes)
    {
        shadowing = ON;
        shadow->setEnabled(true);
    }
    else
    {
        shadowing = OFF;
        shadow->setEnabled(false);
    }

}


void MapCPP::CreateButton()
{
    button = new QPushButton;
    if(shadowing == OFF)
        button->setText("ON");
    else
        button->setText("OFF");
    //connect(button, SIGNAL(clicked()), this, SLOT(ToggleShadow()));
}


void MapCPP::CreateMap()
{
    map = new Esri::ArcGISRuntime::Map(Basemap::darkGrayCanvasVector(this), this);
    widget = new Esri::ArcGISRuntime::MapGraphicsView(map, this);
}


void MapCPP::CreateFrame()
{
    CreateMessage();
    layout = new QGridLayout;
    layout->addWidget(widget, 0, 0);
    layout->addWidget(button, 1, 0, Qt::AlignRight);

    frame = new QFrame();
    //frame->setFrameStyle(QFrame::StyledPanel);
    frame->setStyleSheet("background-color :  rgb(231, 232, 236)");
    frame->setLayout(layout);
}


void MapCPP::ToggleShadow()
{
    if(shadowing == OFF)
    {
        shadow->setEnabled(true);
        button->setText("OFF");
        shadowing = ON;
    }
    else if(shadowing == ON)
    {
        shadow->setEnabled(false);
        button->setText("ON");
        shadowing = OFF;
    }
}


QFrame * MapCPP::GetFrame()
{
    return frame;
}


QGraphicsDropShadowEffect * MapCPP::GetShadow()
{
    return shadow;
}


QPushButton * MapCPP::GetButton()
{
    return button;
}
