#-------------------------------------------------
#
# Project created by QtCreator 2016-10-31T12:48:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoL
TEMPLATE = app
LIBS += -lGLU


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    worker.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    worker.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
