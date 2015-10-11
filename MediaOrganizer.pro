TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /opt/wxWidgets/include/wx-3.0 \
    /opt/wxWidgets/lib/wx/include/gtk3-unicode-3.0

LIBS += -L/opt/wxWidgets/lib \
    -lwx_gtk3u_xrc-3.0 \
    -lwx_gtk3u_html-3.0 \
    -lwx_gtk3u_qa-3.0 \
    -lwx_gtk3u_adv-3.0 \
    -lwx_gtk3u_core-3.0 \
    -lwx_baseu_xml-3.0 \
    -lwx_baseu_net-3.0 \
    -lwx_baseu-3.0

QMAKE_CXXFLAGS +=  -Wno-deprecated-declarations -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__ -pthread

HEADERS += \
    main.h \
    mainwindow.h \
    separator.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    separator.cpp
