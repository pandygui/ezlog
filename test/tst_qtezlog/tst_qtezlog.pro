TEMPLATE = app
QT -= gui
CONFIG   += console
#DEFINES += NO_EZLOG
TARGET = tst_qtezlog
STATICLINK = 0
PROJECTROOT = $$PWD/../..
include($$PROJECTROOT/wrappers/qt/libezlog-qt.pri)
include($$PROJECTROOT/src/libezlog.pri) #TODO: do not depends on libezlog
preparePaths($$OUT_PWD/../../out)

SOURCES += main.cpp
