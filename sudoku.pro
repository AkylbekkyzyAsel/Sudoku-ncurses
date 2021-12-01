TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Sudoku.cpp \
        main.cpp

LIBS += /usr/lib/x86_64-linux-gnu/libncursesw.so

HEADERS += \
    Sudoku.h
