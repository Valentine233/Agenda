#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T17:24:24
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Agenda
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    createnew.cpp \
    opennew.cpp \
    event.cpp

HEADERS  += mainwindow.h \
    createnew.h \
    opennew.h \
    event.h

FORMS    += mainwindow.ui
