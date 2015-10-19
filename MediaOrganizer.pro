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
    pub/videoplayer.h \
    pub/filebrowser.h

PRIVATE_HEADERS += \
    inc/videoframe_p.h \
    inc/thumbnailer.h

CONFIG += link_pkgconfig
PKGCONFIG += gobject-2.0 glib-2.0 libvlc

SOURCES += \
    src/videoframe.c \
    src/videoplayer.c \
    src/thumbnailer.c \
    src/filebrowser.c

HEADERS += \
    $$PUBLIC_HEADERS \
    $$PRIVATE_HEADERS \
    inc/videoplayer_p.h
