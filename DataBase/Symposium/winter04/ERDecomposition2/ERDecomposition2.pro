#-------------------------------------------------
#
# Project created by QtCreator 2014-01-10T03:17:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ERDecomposition2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawer.cpp

HEADERS  += mainwindow.hpp \
    drawer.hpp

FORMS    += mainwindow.ui

CONFIG += c++11
