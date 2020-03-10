#-------------------------------------------------
#
# Project created by QtCreator 2013-07-12T15:30:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = sd_aei
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS    +=  -lopencv_core -lopencv_highgui -lopencv_imgproc
