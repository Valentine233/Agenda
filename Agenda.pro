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
    opennew.cpp \
    event.cpp \
    db.cpp \
    eventlabel.cpp \
    myeventlabel.cpp \
    youreventlabel.cpp

HEADERS  += mainwindow.h \
    opennew.h \
    event.h \
    db.h \
    eventlabel.h \
    myeventlabel.h \
    youreventlabel.h

FORMS    += mainwindow.ui

QT += sql
