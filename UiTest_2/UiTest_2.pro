#-------------------------------------------------
#
# Project created by QtCreator 2014-04-25T17:14:33
#
#-------------------------------------------------

QT       += widgets xml testlib


SOURCES += tst_uitest_2test.cpp \
            ../QTPractice/mainwindow.cpp \
            ../QTPractice/dcminformation.cpp \
            ../QTPractice/imageview.cpp

HEADERS += ../QTPractice/mainwindow.h \
            ../QTPractice/dcminformation.h \
            ../QTPractice/imageview.h \
            ../QTPractice/ui_mainwindow.h

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
