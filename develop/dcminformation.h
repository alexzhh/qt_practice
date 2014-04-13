#ifndef DCMINFORMATION_H
#define DCMINFORMATION_H

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QVector>
#include <QMessageBox>
#include <QImage>
#include "fileinputoutput.h"

//#define PatientID         0x0020
//#define PatientName       0x0010
//#define PatientAge        0x1010
//#define PatientStudyDate (0x0008,0x0020)
//#define PatientStudyTime (0x0008,0x0030)
//#define PatientImageDate (0x0008,0x0023)
//#define PatientImageTime (0x0008,0x0033)

class DcmInformation
   :public FileInputOutput,
    public DcmFileFormat

{
   private:
     QVector <DcmElement*> info;
     void setAttributes(int, int);
     QImage *qimage;
   public:
     DcmInformation();
     ~DcmInformation();
     bool initial(QString);
     bool fileChecksum(); //file check
     QVector <DcmElement*> getAttributes(); //return tags
     template <typename T>
     void MonochromeColorTrans(const T * pixelData);
     uchar colorPalette(float);
     QPixmap drawDcmImage(int width,int height); //return paint pixel object
     void dcm2Xml(QString/*,QString*/);
};

#endif
