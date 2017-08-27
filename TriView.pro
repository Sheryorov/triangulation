#-------------------------------------------------
#
# Project created by QtCreator 2017-03-21T15:15:21
#
#-------------------------------------------------
QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TriView
TEMPLATE = app

SOURCES += main.cpp \
        mainwindow.cpp drawarea.cpp \
        Triangulation.cpp R2Graph.cpp R3Graph.cpp \
        triFunc.cpp scala.cpp

HEADERS  += mainwindow.h drawarea.h \
    Triangulation.h R2Graph.h R3Graph.h \
    triFunc.h scala.h

FORMS    += mainwindow.ui
