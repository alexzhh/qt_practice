#include "savefile.h"
//#include "openfile.h"
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QTextEdit>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include "dcminformation.h"
#include <iostream>
#include <QFile>

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
        DcmFileFormat fileFormat;
        DcmMetaInfo     fileMetaIfo;
        DcmDataset          fileDataset;
        std::ostream& fileStream=COUT;
        QXmlStreamReader xmlReader;

        QFile file(fileName.toStdString().c_str());
        if(!file.open(QIODevice::ReadWrite))
            return false;


        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
    QString out;
//       QFile file(fileName);
//        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
//        {
//            return false;
//        }
//   //     QTextStream out(&file);
     //   fileFormat.insert(fileItems.writeXML(fileStream.write(openfilepath.toStdString().c_str(),std::ifstream::binary)).text());
        //qDebug()<<"<?xml version=\"1.0\" encoding=\"windows-1252\"?>"\
           //    <<fileFormat.writeXML()
          //   <<dcmMe.writeXML(fileStream.write(openfilepath.toStdString().c_str(),std::ifstream::binary)).text()<<"++++++++++++++++++++++++++++++";
         out=doc.getDcmData().writeXML(fileStream.write(openfilepath.toStdString().c_str(),std::ifstream::binary)).text();
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("sknd");
        xmlWriter.writeEndDocument();


    }
    }
    }
    return true;
}



