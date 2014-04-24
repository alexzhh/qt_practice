#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T14:38:09
#
#-------------------------------------------------



QT       += testlib

QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../ImageTest/imagetest
CONFIG   += console testlib
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += imagetest.cpp\
    ../QTPractice/imageview.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../QTPractice/imageview.cpp


#DCMTK Lib setings for mac
mac*{
    DCMTK_HOME = /Users/phoenix/dcmtkLib
    INCLUDEPATH += $${DCMTK_HOME}/include
    LIB_PATH = $${DCMTK_HOME}/lib
    LIBS +=  -L$${LIB_PATH}
    LIBS +=  -ldcmdata -ldcmimage -ldcmimgle -lofstd -loflog -lz
}

#DCMTK Lib setings for Linux
unix:!macx{
INCLUDEPATH += ../dcmtk360/include

LIBS +=  -ldcmdata -ldcmimage -ldcmimgle -lofstd -loflog -lz
}
#DCMTK Lib setings for Windows
win32{
INCLUDEPATH += "D:/Qt/DCMTK/include"
    debug {
        LIBS +=  -L"D:\Qt\DCMTK\lib" -ldcmdata -ldcmimage -ldcmimgle -lofstd -loflog \
                 -lAdvAPI32 -lWS2_32 -lnetapi32
    }
    release {
        LIBS +=  -L"D:\Qt\DCMTK\lib-release" -ldcmdata -ldcmimage -ldcmimgle -lofstd -loflog \
                 -lAdvAPI32 -lWS2_32 -lnetapi32
    }
}
