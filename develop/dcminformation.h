#ifndef DCMINFORMATION_H
#define DCMINFORMATION_H

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <QVector>
#include <QMessageBox>

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
     QVector <DcmElement*> info;  //save the DcmElement element
     void setAttributes(Uint16, Uint16); //set the DcmElement element to QVector<DcmElement*>
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
     void saveDcmFile();  //save file as dcm
     void saveXmlFile();  //save file as xml
     QVector <DcmElement*> getAttributes(); // return selected elements (DcmElement)
     void setOutputFile(const QString &oPath); //set Output File path (OutputFilePath)
     QString getInputFile(); // get Input File path (inputFilePath)
     QString getOutputFile();// get Output File path (OutputFilePath)
};

#endif
