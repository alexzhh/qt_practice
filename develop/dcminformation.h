#ifndef DCMINFORMATION_H
#define DCMINFORMATION_H

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QVector>
#include <QtXml/QDomDocument>
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

typedef struct AttrElements
{
  int type;
  QString vr;
  QString value;
  bool operator ==(AttrElements &other)
  {
    return (type == other.type &&
            vr   == other.vr   &&
            value== other.value );
  }

}AttrElements;

class DcmInformation
   :public FileInputOutput,
    public DcmFileFormat

{
   private:
     QVector <AttrElements> info;
   public:
     DcmInformation();
     ~DcmInformation();
     BOOL initial(QString);
     BOOL fileChecksum();           //file check
     void setAttributes(int, int, int);
     QVector <AttrElements> getAttributes(); //return tags
     QPixmap drawDcmImage(int width,int height); //return paint pixel object
//     QDomDocument dcm2Xml();
};

#endif
