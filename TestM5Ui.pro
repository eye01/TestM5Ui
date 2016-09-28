#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T16:35:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestM5Ui
TEMPLATE = app

DESTDIR = $$PWD/../bin/
OBJECTS_DIR = $$PWD/obj
MOC_DIR = $$PWD/obj
UI_DIR = $$PWD/obj/ui_header

INCLUDEPATH +=$$PWD/../

SOURCES += main.cpp\
        widget.cpp \
    TableModel.cpp \
    LayerStock.cpp \
    ModelStock.cpp \
    LayerChartBase.cpp

HEADERS  += widget.h \
    tools_export.h \
    TableModel.h \
    LayerStock.h \
    ModelStock.h \
    LayerChartBase.h

FORMS    += widget.ui \
    LayerStock.ui

unix:!macx: LIBS += -L$$PWD/../KDChart-2.6.0/lib/ -ltesttools

INCLUDEPATH += $$PWD/../KDChart-2.6.0/include/KDGantt
DEPENDPATH += $$PWD/../KDChart-2.6.0/include/KDGantt

unix:!macx: LIBS += -L$$PWD/../KDChart-2.6.0/lib/ -lkdchart

INCLUDEPATH += $$PWD/../KDChart-2.6.0/include/KDChart
DEPENDPATH += $$PWD/../KDChart-2.6.0/include/KDChart

INCLUDEPATH += $$PWD/../KDChart-2.6.0/examples/tools
DEPENDPATH += $$PWD/../KDChart-2.6.0/examples/tools

win32: LIBS += -L$$PWD/../KDChart-2.6.0/lib/win32 -lkdchart2 -ltesttools2
