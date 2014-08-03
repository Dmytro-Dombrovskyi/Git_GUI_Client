#-------------------------------------------------
#
# Project created by QtCreator 2014-07-25T23:26:48
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS   += -std=c++11
QMAKE_CFLAGS_WARN_ON    = -Wall

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Git_Gui_Client
TEMPLATE = app


SOURCES += main.cpp\
    gui_main_window.cpp \
    gitdata.cpp \
    my_data_model.cpp \
    seconddatamodel.cpp

HEADERS  += \
    gui_main_window.h \
    gitdata.h \
    my_data_model.h \
    seconddatamodel.h

FORMS    += \
    gui_main_window.ui

RESOURCES += \
    Images.qrc

OTHER_FILES +=
