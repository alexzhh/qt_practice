#-------------------------------------------------
#
# Project created by QtCreator 2014-04-01T09:40:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTPractice
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        dcminformation.cpp \
        imageview.cpp

HEADERS  += mainwindow.h\
        dcminformation.h \
        imageview.h

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

FORMS    += \
    mainwindow.ui
