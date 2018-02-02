#-------------------------------------------------
#
# Project created by QtCreator 2018-02-02T09:56:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecipeDB
TEMPLATE = app


SOURCES += sources/main.cpp \
    sources/mainwindow.cpp \
    SQLite/sqlite3.c

HEADERS  += \
    headers/mainwindow.h \
    SQLite/sqlite3.h \
    SQLite/sqlite3ext.h

FORMS    += gui/mainwindow.ui

DISTFILES += \
    .gitignore
