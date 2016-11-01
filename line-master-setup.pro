#-------------------------------------------------
#
# Project created by QtCreator 2016-10-24T10:34:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = line-master-setup
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialclient.cpp

HEADERS  += mainwindow.h \
    serialclient.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -lserial

RESOURCES += \
    images.qrc
