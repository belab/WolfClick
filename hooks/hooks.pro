#-------------------------------------------------
#
# Project created by QtCreator 2013-02-21T22:15:30
#
#-------------------------------------------------

TARGET = hooks
TEMPLATE = lib

DEFINES += HOOKS_LIBRARY

SOURCES += hooks.cpp

HEADERS += hooks.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
