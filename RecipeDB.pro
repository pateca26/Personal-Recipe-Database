
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecipeDB
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    recipes.cpp

HEADERS  += login.h \
    recipes.h

FORMS    += login.ui \
    recipes.ui
