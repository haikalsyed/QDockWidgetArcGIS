TEMPLATE = app
TARGET = MapLoader

QT += qml
QT += core gui
QT += network
QT += location
QT += quickwidgets

CONFIG += c++11 esri_runtime_qt

ARCGIS_RUNTIME_VERSION = 100.5
include(/Users/Administrator/Documents/MapLoader/esri_runtime_qt.pri)
include(/Users/Administrator/Documents/MapLoader/arcgis_runtime_toolkit_cpp.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  main.cpp \
    mapcpp.cpp \
    mapqml.cpp \
    window.cpp

HEADERS += \
    mapcpp.h \
    mapcreator.h \
    mapqml.h \
    window.h

DISTFILES += \
    Map.qml \
    OSMMap.qml

RESOURCES += \
    resource.qrc
