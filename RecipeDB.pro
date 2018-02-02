#-------------------------------------------------
#
# Project created by QtCreator 2018-02-02T09:56:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecipeDB
TEMPLATE = app


SOURCES += SQLite/sqlite3.c \
    model/recipe/ingredient.cpp \
    model/recipe/instruction.cpp \
    model/recipe/recipe.cpp \
    model/recipe/recipeingredient.cpp \
    userInterface/mainwindow.cpp \
    main.cpp \
    model/database/database.cpp

HEADERS  += SQLite/sqlite3.h \
    SQLite/sqlite3ext.h \
    model/recipe/ingredient.h \
    model/recipe/instruction.h \
    model/recipe/recipe.h \
    model/recipe/recipeingredient.h \
    userInterface/mainwindow.h \
    model/database/database.h

FORMS    += gui/mainwindow.ui

DISTFILES += \
    .gitignore

RESOURCES += \
    gui/menubuttonstylesheet.qrc
