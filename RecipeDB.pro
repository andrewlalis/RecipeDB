#-------------------------------------------------
#
# Project created by QtCreator 2018-02-02T09:56:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecipeDB
TEMPLATE = app


SOURCES += model/recipe/instruction.cpp \
    model/recipe/recipe.cpp \
    main.cpp \
    model/database/database.cpp \
    model/recipe/ingredients/ingredient.cpp \
    model/recipe/ingredients/ingredientlistmodel.cpp \
    model/recipe/tags/recipetag.cpp \
    SQLite/sqlite3.c \
    model/database/resulttable.cpp \
    model/database/recipedatabase.cpp \
    utils/fileutils.cpp \
    gui/newrecipedialog.cpp \
    model/recipe/tags/taglistmodel.cpp \
    gui/newDialogs/newingredientdialog.cpp \
    gui/newDialogs/newtagdialog.cpp \
    gui/newDialogs/newunitdialog.cpp \
    utils/aspectratiopixmaplabel.cpp \
    utils/stringutils.cpp \
    gui/openrecipedialog.cpp \
    model/recipe/recipetablemodel.cpp \
    gui/mainwindow.cpp \
    gui/newDialogs/newfoodgroupdialog.cpp

HEADERS  += model/recipe/instruction.h \
    model/recipe/recipe.h \
    model/database/database.h \
    model/recipe/ingredients/ingredient.h \
    model/recipe/ingredients/ingredientlistmodel.h \
    model/recipe/tags/recipetag.h \
    SQLite/sqlite3.h \
    SQLite/sqlite3ext.h \
    model/database/resulttable.h \
    model/database/recipedatabase.h \
    utils/fileutils.h \
    gui/newrecipedialog.h \
    model/recipe/tags/taglistmodel.h \
    gui/newDialogs/newingredientdialog.h \
    gui/newDialogs/newtagdialog.h \
    gui/newDialogs/newunitdialog.h \
    utils/aspectratiopixmaplabel.h \
    utils/stringutils.h \
    gui/openrecipedialog.h \
    model/recipe/recipetablemodel.h \
    gui/mainwindow.h \
    gui/newDialogs/newfoodgroupdialog.h

LIBS += -ldl \

FORMS    += gui/mainwindow.ui \
    gui/newrecipedialog.ui \
    gui/newDialogs/newingredientdialog.ui \
    gui/newDialogs/newtagdialog.ui \
    gui/newDialogs/newunitdialog.ui \
    gui/openrecipedialog.ui \
    gui/mainwindow.ui \
    gui/newDialogs/newfoodgroupdialog.ui

DISTFILES += \
    .gitignore

RESOURCES += \
    res.qrc
