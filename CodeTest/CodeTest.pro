#-------------------------------------------------
#
# Project created by QtCreator 2014-04-21T19:43:43
#
#-------------------------------------------------

QT       += widgets testlib

QT       -= gui

TARGET = tst_codetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_codetest.cpp \
           ../QTPractice/dcminformation.cpp\
           ../QTPractice/imageview.cpp\


DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
           ../QTPractice/dcminformation.h\
           ../QTPractice/imageview.h\



#DCMTK Lib
win32{
INCLUDEPATH += "D:/Qt/DCMTK/include"
    debug {
        LIBS +=  -L"D:\Qt\DCMTK\lib" -ldcmdata -ldcmimage -ldcmimgle -lofstd -loflog \
                 -lAdvAPI32 -lWS2_32 -lnetapi32
    }
    release {
        LIBS +=  -L"C:\Program Files\DCMTK\lib-release" -ldcmdata -ldcmimage -ldcmimgle -lofstd -loflog \
                 -lAdvAPI32 -lWS2_32 -lnetapi32

    }
}

#DCMTK Lib setings for mac
mac*{
    DCMTK_HOME = /Users/phoenix/dcmtkLib
    INCLUDEPATH += $${DCMTK_HOME}/include
    LIB_PATH = $${DCMTK_HOME}/lib
    LIBS +=  -L$${LIB_PATH}
    LIBS +=  -ldcmdata -ldcmimage -ldcmimgle -lofstd -loflog -lz
}