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
    model/recipe/instruction.cpp \
    model/recipe/recipe.cpp \
    userInterface/mainwindow.cpp \
    main.cpp \
    model/database/database.cpp \
    model/recipe/ingredients/unitofmeasure.cpp \
    model/recipe/ingredients/ingredient.cpp \
    model/recipe/ingredients/ingredientlistmodel.cpp \
    model/recipe/ingredients/recipeingredient.cpp \
    model/recipe/tags/recipetag.cpp

HEADERS  += SQLite/sqlite3.h \
    SQLite/sqlite3ext.h \
    model/recipe/instruction.h \
    model/recipe/recipe.h \
    userInterface/mainwindow.h \
    model/database/database.h \
    model/recipe/ingredientlistmodel.h \
    model/recipe/ingredients/unitofmeasure.h \
    model/recipe/ingredients/ingredient.h \
    model/recipe/ingredients/ingredientlistmodel.h \
    model/recipe/ingredients/recipeingredient.h \
    model/recipe/tags/recipetag.h

FORMS    += gui/mainwindow.ui

DISTFILES += \
    .gitignore

RESOURCES +=
