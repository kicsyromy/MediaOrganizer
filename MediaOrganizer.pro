#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T12:30:59
#
#-------------------------------------------------

QT       -= core gui

TARGET = mo
TEMPLATE = lib

DEFINES += MO_LIB

CONFIG += link_pkgconfig
PKGCONFIG += glib-2.0 libvlc

SOURCES += mo.cpp \
    videoplayer.cpp

HEADERS += mo.h \
    mo_global.h \
    videoplayer.h
