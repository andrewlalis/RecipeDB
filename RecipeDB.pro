#-------------------------------------------------
#
# Project created by QtCreator 2018-02-02T09:56:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecipeDB
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp

HEADERS  += \
    headers/mainwindow.h

FORMS    += mainwindow.ui \
    gui/mainwindow.ui

DISTFILES += \
    .gitignore
