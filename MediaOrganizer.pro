#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T12:30:59
#
#-------------------------------------------------

QT       -= core gui

TARGET = mo
TEMPLATE = lib

DEFINES += MO_LIB

INCLUDEPATH += \
    inc \
    pub

PUBLIC_HEADERS += \
    pub/mo_global.h \
    pub/videoplayer.h \
    pub/videoframe.h

PRIVATE_HEADERS += \
    inc/videoframe_def.h

CONFIG += link_pkgconfig
PKGCONFIG += gobject-2.0 glib-2.0 libvlc

SOURCES += \
    src/videoframe.c \
    src/videoplayer.c

HEADERS += \
    $$PUBLIC_HEADERS \
    $$PRIVATE_HEADERS
