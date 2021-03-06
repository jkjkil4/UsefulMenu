#-------------------------------------------------
#
# Project created by QtCreator 2020-05-16T08:33:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UsefulMenu
TEMPLATE = app

RC_ICONS += A.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += WIN32_LEAN_AND_MEAN

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += main.cpp \
    Class/extensionitem.cpp \
    Class/globalshortcut.cpp \
    Widget/iconbtn.cpp \
    Widget/menubar.cpp \
    Widget/settingswidget.cpp \
    Widget/shortcutedit.cpp \
    mainwidget.cpp

HEADERS += \
    Class/extensionitem.h \
    Class/globalshortcut.h \
    Class/lib.h \
    Class/libmanager.h \
    Widget/iconbtn.h \
    Widget/menubar.h \
    Widget/settingswidget.h \
    Widget/shortcutedit.h \
    mainwidget.h \
    namespace.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# include
include( $$PWD/../../_1Classes/qxtglobalshortcut5-master/qxt.pri )


# ButtonTable
win32: LIBS += -L$$PWD/Libs/ -lButtonTable

INCLUDEPATH += $$PWD/Libs/ButtonTable/ButtonTable
DEPENDPATH += $$PWD/Libs/ButtonTable/ButtonTable

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/Libs/ButtonTable.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/Libs/libButtonTable.a

RESOURCES += \
    resource.qrc
