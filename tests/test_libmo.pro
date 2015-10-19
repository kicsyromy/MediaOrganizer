QT       -= core gui

TARGET = test_libmo
TEMPLATE = app
CONFIG += console

INCLUDEPATH += \
    ../pub \
    ../inc

LIBS += -L../../build-MediaOrganizer-Qt_5_2_1_Desktop_GCC_64bit-Debug -lmo

CONFIG += link_pkgconfig
PKGCONFIG += gobject-2.0 glib-2.0 libvlc

SOURCES += \
    main.c \
    test_videoplayer.c

HEADERS += \
    test_videoplayer.h
