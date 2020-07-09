TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = bfrc
DESTDIR = ../bfrc/bin/

SOURCES += \
        algoritomos.c \
        arboles.c \
        main.c

HEADERS += \
    algoritomos.h \
    arboles.h
