TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    monde.cpp \
    tuile.cpp \
    evenement.cpp \
    deplacement.cpp \
    exceptiongame.cpp


LIBS += -L C:/SDL-1.2.15/lib -lSDL -lSDL_image

INCLUDEPATH += C:/SDL-1.2.15/include/SDL
INCLUDEPATH += C:/SDL_image-1.2.10/include

QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors

HEADERS += \
    monde.h \
    tuile.h \
    TypeTuile.h \
    evenement.h \
    deplacement.h \
    exceptiongame.h

OTHER_FILES +=
