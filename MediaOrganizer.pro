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
    pub/videoframe.h \
    pub/videoplayer.h

PRIVATE_HEADERS += \
    inc/videoframe_p.h \
    inc/thumbnailer.h

CONFIG += link_pkgconfig
PKGCONFIG += gobject-2.0 glib-2.0 libvlc

SOURCES += \
    src/videoframe.c \
    src/videoplayer.c \
    src/thumbnailer.c

HEADERS += \
    $$PUBLIC_HEADERS \
    $$PRIVATE_HEADERS
