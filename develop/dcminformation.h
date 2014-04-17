#ifndef DCMINFORMATION_H
#define DCMINFORMATION_H

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QVector>
#include <QMessageBox>
#include <QImage>

//#define PatientID         0x0020
//#define PatientName       0x0010
//#define PatientAge        0x1010
//#define PatientStudyDate (0x0008,0x0020)
//#define PatientStudyTime (0x0008,0x0030)
//#define PatientImageDate (0x0008,0x0023)
//#define PatientImageTime (0x0008,0x0033)

class DcmInformation
   : public DcmFileFormat

{
   private:
     QVector <DcmElement*> info;

     void setAttributes(int, int);
     QImage *qimage;
     int Image_width;
     int Image_height;

     QString inputFilePath; // Loading file path
     QString outputFilePath; // saving file path
     bool loaded;


   public:
     DcmInformation(QString iPath, QString oPath="");
     ~DcmInformation();

     bool loadFromDCM(); // load DCM data from *.dcm (inputFilePath)
     QString getStringlizeTag(const DcmTag& dcmtag);
     bool endOfDataSet(const DcmTag& dcmtag);
     bool isValid(); // check file format
     void customSaveFile();
     int getSavedFileType();
     void saveDcmFile();
     void saveXmlFile();
     QVector <DcmElement*> getAttributes(); // return tags
     template <typename T>
     void MonochromeColorTrans(const T * pixelData); // set pixel data
     uchar colorPalette(float);
     QPixmap drawDcmImage(int width, int height); //return paint pixel object
     void setOutputFile(QString oPath);
     QString getInuptFile();
     bool isLoaded();
     void drawMonochrome(DicomImage &dicomImage, int width, int height);
     void drawRGB(DicomImage &dicomImage, int width, int height);
     void prepareQImage(DicomImage &dicomImage, QImage::Format FormatType, int width, int height);
     void drawMonochromeAlux(DicomImage &dicomImage);
     void drawRGBAlux(DicomImage &dicomImage);
};

#endif
