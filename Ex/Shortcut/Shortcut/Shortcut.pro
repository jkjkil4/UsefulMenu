#-------------------------------------------------
#
# Project created by QtCreator 2020-08-14T16:54:04
#
#-------------------------------------------------

QT       += widgets

TARGET = Shortcut
TEMPLATE = lib

DEFINES += SHORTCUT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Class/global.cpp \
        Class/shortcutitem.cpp \
        Widget/iconbtn.cpp \
        Widget/menubar.cpp \
        Widget/pathdialog.cpp \
        Widget/shortcutwidget.cpp \
        shortcut.cpp

HEADERS += \
        Class/global.h \
        Class/shortcutitem.h \
        Widget/iconbtn.h \
        Widget/menubar.h \
        Widget/pathdialog.h \
        Widget/shortcutwidget.h \
        header.h \
        shortcut.h \
        shortcut_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32: LIBS += -L$$PWD/../../../Libs/ -lButtonTable

INCLUDEPATH += $$PWD/../../../Libs/ButtonTable/ButtonTable
DEPENDPATH += $$PWD/../../../Libs/ButtonTable/ButtonTable

RESOURCES += \
    resource.qrc
