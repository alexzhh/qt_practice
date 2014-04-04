#ifndef DCMINFORMATION_H
#define DCMINFORMATION_H

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QVector>
#include <QString>
#include <QtXml/QDomDocument>
#include <QMessageBox>
#include <QImage>

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
{
   private:
     QVector <AttrElements> info;
     DcmDataset *data;
   public:
     DcmInformation();
     ~DcmInformation();
     void openDcmFile(QString);        //打开dcm文件
     void fileChecksum();           //文件的校验
     void setAttributes(int tag1, int tag2, int num);
     QVector <AttrElements> getAttributes(); //返回五个tag 以及 相应的value
     DcmDataset *getDcmData();    //返回dcm数据
     QPixmap drawDcmImage(QString);  //返回绘图指针
     QDomDocument dcm2Xml(); //以下三个可先不实现
     void saveDcmAs();
     void saveXml();
};
#endif
