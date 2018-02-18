TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    baseclass.cpp \
    gametoken.cpp \
    gameboard.cpp

HEADERS += \
    baseclass.h \
    gametoken.h \
    gameboard.h

DISTFILES += \
    README
