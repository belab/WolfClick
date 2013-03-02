#-------------------------------------------------
#
# Project created by QtCreator 2013-02-21T22:11:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wolfclick
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customwidget.cpp

HEADERS  += mainwindow.h \
    customwidget.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../hooks/release/ -lhooks
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../hooks/debug/ -lhooks

#INCLUDEPATH += $$PWD/../hooks
#DEPENDPATH += $$PWD/../hooks
