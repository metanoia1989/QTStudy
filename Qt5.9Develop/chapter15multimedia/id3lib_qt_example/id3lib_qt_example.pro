#-------------------------------------------------
#
# Project created by QtCreator 2015-09-05T18:09:13
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = id3lib_qt_example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    id3lib/include/id3.h

FORMS    += mainwindow.ui

INCLUDEPATH += id3lib/include

LIBS += -lD:/WorkSpace/QT/QTStudy/Qt5.9Develop/chapter15multimedia/id3lib_qt_example/id3lib/bin/Release/id3lib
