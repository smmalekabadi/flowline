QT += core
QT -= gui

TARGET = CSProblem
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    pathgenerator.cpp \
    outlet.cpp \
    satisfyer.cpp

HEADERS += \
    outlet.h \
    satisfyer.h

