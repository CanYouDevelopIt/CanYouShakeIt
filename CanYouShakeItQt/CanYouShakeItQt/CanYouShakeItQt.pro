#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T15:10:48
#
#-------------------------------------------------

QT       += core gui \
            multimedia \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CanYouShakeItQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    shakemanager.cpp \
    joueur.cpp \
    score.cpp

HEADERS  += mainwindow.h \
    shakemanager.h \
    joueur.h \
    score.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:\OpenCV2411\opencv\build\include"

LIBS += -LC:\OpenCV2411\opencv\build\x64\vc12\lib\
-lopencv_core2411d\
-lopencv_highgui2411d\
-lopencv_imgproc2411d\

RESOURCES += \
    Music/res.qrc \
