#include "savefile.h"
//#include "openfile.h"
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QTextEdit>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include "dcminformation.h"


savefile::savefile(QWidget *parent) :
    QWidget(parent)
{
}


bool savefile::saveFile(QString fileName,QString openfilepath)
{
    DcmInformation doc;
    if(!openfilepath.isEmpty())
    {
    doc.openDcmFile(openfilepath.toStdString().c_str());
    if(!doc.getDcmData().isEmpty())
    {
        if(fileName.endsWith(".dcm"))
    doc.getDcmData().saveFile(fileName.toStdString().c_str());
    if(fileName.endsWith(".xml"))
    {
    qDebug()<<tr("save as XML");
    //    doc.saveXml();
    }
    }

    }




    return true;
}


