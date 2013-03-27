#-------------------------------------------------
#
# Project created by QtCreator 2013-03-27T10:29:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += network

TARGET = YMapDemo
TEMPLATE = app

INCLUDEPATH += widget YMapStaticAPI

SOURCES += main.cpp\
        mainwindow.cpp \
    widget/MapWidget.cpp \
    YMapStaticAPI/MapImageLoader.cpp \
    YMapStaticAPI/MapParams.cpp

HEADERS  += mainwindow.h \
    widget/MapWidget.h \
    YMapStaticAPI/MapImageLoader.h \
    YMapStaticAPI/MapParams.h

FORMS    += mainwindow.ui
