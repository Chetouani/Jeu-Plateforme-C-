TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors

INCLUDEPATH += $$PWD/SDL/include/SDL
DEPENDPATH += $$PWD/SDL/include/SDL

INCLUDEPATH += $$PWD/SDL/lib
DEPENDPATH += $$PWD/SDL/lib

SOURCES += main.cpp \
    monde.cpp \
    tuile.cpp \
    evenement.cpp \
    deplacement.cpp \
    exceptiongame.cpp \
    gestionjeu.cpp \
    mainwindow.cpp

LIBS += -L SDL/lib/ -lmingw32 -lSDLmain -llibSDL -lSDL_image -lSDL_ttf

HEADERS += \
    monde.h \
    tuile.h \
    TypeTuile.h \
    evenement.h \
    deplacement.h \
    exceptiongame.h \
    gestionjeu.h \
    mainwindow.h

OTHER_FILES +=

RESOURCES += \
    images.qrc

FORMS += \
    mainwindow.ui
