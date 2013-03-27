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

INCLUDEPATH += widget

SOURCES += main.cpp\
        mainwindow.cpp \
    widget/MapWidget.cpp

HEADERS  += mainwindow.h \
    widget/MapWidget.h

FORMS    += mainwindow.ui
