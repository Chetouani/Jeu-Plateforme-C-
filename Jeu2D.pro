TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

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
    exceptiongame.cpp

LIBS += -L SDL/lib/ -lmingw32 -lSDLmain -llibSDL -lSDL_image -lSDL_ttf

HEADERS += \
    monde.h \
    tuile.h \
    TypeTuile.h \
    evenement.h \
    deplacement.h \
    exceptiongame.h

OTHER_FILES +=
