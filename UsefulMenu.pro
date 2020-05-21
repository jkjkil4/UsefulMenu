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

SOURCES += \
        Class/iconbtn.cpp \
        Class/line.cpp \
        Widget/GetScreen/Area/areapoint.cpp \
        Widget/GetScreen/Area/horarea.cpp \
        Widget/GetScreen/Area/verarea.cpp \
        Widget/GetScreen/ButtonMenu/buttonmenu.cpp \
        Widget/GetScreen/getscreen.cpp \
        Widget/ball.cpp \
        Widget/btnlist.cpp \
        main.cpp \
        Class/rammonitor.cpp \
        widget.cpp

HEADERS += \
        Class/iconbtn.h \
        Class/line.h \
        Widget/GetScreen/Area/areaparent.h \
        Widget/GetScreen/Area/areapoint.h \
        Widget/GetScreen/Area/horarea.h \
        Widget/GetScreen/Area/verarea.h \
        Widget/GetScreen/ButtonMenu/buttonmenu.h \
        Widget/GetScreen/getscreen.h \
        Widget/ball.h \
        Class/global.h \
        Class/rammonitor.h \
        Widget/btnlist.h \
        widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include( $$PWD/../../_1Classes/JQCPUMonitor/JQLibrary/JQCPUMonitor.pri )

RESOURCES += \
    resource.qrc
