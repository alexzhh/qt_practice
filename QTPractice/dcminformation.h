#ifndef DCMINFORMATION_H
#define DCMINFORMATION_H

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <QMap>
#include <QList>
#include <QMessageBox>
#include "imageview.h"

//#define PatientID         0x0020
//#define PatientName       0x0010
//#define PatientAge        0x1010
//#define PatientStudyDate (0x0008,0x0020)
//#define PatientStudyTime (0x0008,0x0030)
//#define PatientImageDate (0x0008,0x0023)
//#define PatientImageTime (0x0008,0x0033)

enum FileFliter{
    Type_XML,   //xml
    Type_DCM,   //dcm
    Type_UNKNOW //unknow
};//file fliter

class DcmInformation
   : public DcmFileFormat
{
  private:
     QString inputFilePath; // Loading file path
     QString outputFilePath; // saving file path

   public:
     DcmInformation(QString iPath, QString oPath = "");//initial Loading file path
     ~DcmInformation();

     bool loadFromDCM(); // load DCM data from *.dcm (inputFilePath)
     QString getStringlizeTag(const DcmTag& dcmtag); // return (GroupNum, ElementNum) as string
     bool endOfDataSet(const DcmTag& dcmtag);//check whether file Dataset end
     bool isValid(); // check file format
     void customSaveFile(); //save *.dcm or *.xml file
     FileFliter getSavedFileType(); //get save file type (dcm or xml)
     bool saveDcmFile();  //save file as dcm
     bool saveXmlFile();  //save file as xml
     QMap <QString, QPair<ushort, ushort> > getAttributes(const QList<QString> &tagname);
     QString getDcmQStringValue(ushort gtag, ushort etag);
     void setOutputFile(const QString &oPath); //set Output File path (OutputFilePath)
     QString getInputFile(); // get Input File path (inputFilePath)
     QString getOutputFile();// get Output File path (OutputFilePath)
     QPixmap drawDcmImage(int width,int height); //draw image return QPixmap
     bool putAndInsertString(const QString tagname, const QString& value);
     bool putAndInsertString(ushort gtag, ushort etag, const QString& value);
     //Change the value replaced the original value of tag
     bool checkEachTag(ushort gtag, ushort etag, const char * value);
     //Check the validity of each tag (input tag)
     bool checkEachTag(const DcmEVR &dcmevr, const char * value);
     //Check the validity of each tag (input DcmEVR)
     bool checkEachTag(const QString tagname, const char *value);
     //Check the validity of each tag (input TagName)
//     Elementinfo findTagFromTagName(const QString tagname);
     //give tagname to find tag return Elementinfo
};

#endif
