QT       -= core gui

TARGET = test_libmo
TEMPLATE = app
CONFIG += console

DEFINES += TEST_DATA_PATH=\\\"$${_PRO_FILE_PWD_}/data/\\\"

INCLUDEPATH += \
    ../pub \
    ../inc

LIBS += -LD:/workspace/build-MediaOrganizer-MSYS2_MinGW_GCC_32bit-Debug/debug/ -lmo

CONFIG += link_pkgconfig
PKGCONFIG += gobject-2.0 glib-2.0 libvlc

SOURCES += \
    main.c \
    test_videoplayer.c

HEADERS += \
    test_videoplayer.h \
    test_global.h
