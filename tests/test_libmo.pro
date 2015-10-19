QT       -= core gui

TARGET = test_libmo
TEMPLATE = app
CONFIG += console

INCLUDEPATH += \
    ../pub \
    ../inc

CONFIG += link_pkgconfig
PKGCONFIG += gobject-2.0 glib-2.0

SOURCES += \
    main.c \
    test_videoplayer.c

HEADERS += \
    test_videoplayer.h
