#include "dcminformation.h"


DcmInformation::DcmInformation()
{

}


DcmInformation::~DcmInformation()
{

}


BOOL DcmInformation::initial()
{
   OFCondition oc = this->loadFile(
     OpenFile("DCM File(*.dcm)").toStdString().c_str());
   if(oc.bad() || fileChecksum())
     return FALSE;

   return TRUE;
}


void DcmInformation::setAttributes(int tag1, int tag2, int num)
{
   DcmElement * element;
   OFString ofstr;
   AttrElements attres;

   if(this->getDataset()->findAndGetElement(DcmTagKey(tag1,tag2),element).good())
   {
     attres.type = num;
     attres.vr = element->getTag().getVRName();
     element->getOFString(ofstr,0);
     attres.value = QString::fromStdString(ofstr.c_str());
     if(tag1==0x0008)
     {
       if(this->getDataset()->findAndGetElement(DcmTagKey(tag1,tag2 + 0x0010),element).good())
       {
         element->getOFString(ofstr,0);
         attres.value += " " + QString::fromStdString(ofstr.c_str());
       }
     }
    }
   else
   {
     attres.type = 0;
     attres.vr = attres.value = "";
     //errorMessage
   }

   info.append(attres);
}


QVector <AttrElements> DcmInformation::getAttributes()
{
   setAttributes(0x0010,0x0020,0);
   setAttributes(0x0010,0x0010,1);
   setAttributes(0x0010,0x1010,2);
   setAttributes(0x0008,0x0020,3);
   setAttributes(0x0008,0x0023,4);

   return info;
}


BOOL DcmInformation::fileChecksum()
{
   OFCondition oc = this->validateMetaInfo(
       this->getDataset()->getOriginalXfer());
   if(oc.good())
     return FALSE;

   return TRUE;
}


QPixmap DcmInformation::drawDcmImage(int width, int height)
{
   E_TransferSyntax transf = this->getDataset()->getOriginalXfer();
   DicomImage dicom( this->getDataset(),
                     transf,
                     CIF_AcrNemaCompatibility, 0, 1);
   //set window center and width
   dicom.setWindow(512,1024);
   dicom.writeBMP("c:\\dicom.bmp",8);
   QImage qimage("c:\\dicom.bmp");
   QFile::remove("c:\\dicom.bmp");
   return QPixmap::fromImage(qimage.scaled(width,height));
   //return NULL;
}

