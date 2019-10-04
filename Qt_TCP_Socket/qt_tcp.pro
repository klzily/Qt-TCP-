#-------------------------------------------------
#
# Project created by QtCreator 2017-10-23T22:11:27
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_tcp
TEMPLATE = app


SOURCES += main.cpp\
        servewidget.cpp \
    clientwidget.cpp

HEADERS  += servewidget.h \
    clientwidget.h

FORMS    += servewidget.ui \
    clientwidget.ui
CONFIG += C++11
