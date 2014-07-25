#-------------------------------------------------
#
# Project created by QtCreator 2014-07-25T23:26:48
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS   += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Git_Gui_Client
TEMPLATE = app


SOURCES += main.cpp\
        git_gui_client.cpp

HEADERS  += git_gui_client.h

FORMS    += git_gui_client.ui

RESOURCES += \
    icons.qrc
