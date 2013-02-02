#-------------------------------------------------
#
# Project created by QtCreator 2013-02-02T12:09:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mochat
TEMPLATE = app

unix:!macx: LIBS += -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_program_options -lboost_system

SOURCES += main.cpp\
        mainwindow.cpp \
    messagereceiver.cpp

HEADERS  += mainwindow.h \
    messagereceiver.h

FORMS    += mainwindow.ui
