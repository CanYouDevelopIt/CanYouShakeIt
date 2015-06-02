#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T15:24:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM_CanYousShakeIt
TEMPLATE = app

INCLUDEPATH += C:\Users\Yolo\Desktop\OpenCV2411\opencv\sources\include
LIBS += -LC:\Users\Yolo\Desktop\OpenCV2411\opencv\build\x64\vc12\lib
-lopencv_core249\
-lopencv_highgui249\
-lopencv_imgproc249\

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
