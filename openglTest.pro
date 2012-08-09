#-------------------------------------------------
#
# Project created by QtCreator 2012-06-19T10:31:51
#
#-------------------------------------------------

QT       += core gui opengl glew

TARGET = openglTest
TEMPLATE = app
CONFIG += console

SOURCES += main.cpp\
    glwidget.cpp \
    meshdata.cpp \
    vert.cpp \
    cylinder.cpp \
    mainwindow.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    meshdata.h \
    vert.h \
    cylinder.h

FORMS    += mainwindow.ui

LIBS += -lGLEW -lGLU -lGL
