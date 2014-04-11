#include "dcminformation.h"


DcmInformation::DcmInformation()
{

}


DcmInformation::~DcmInformation()
{

}


BOOL DcmInformation::initial(QString OpenPath)
{
   OFCondition oc = this->loadFile(OpenPath.toStdString().c_str());

   if(oc.bad() || fileChecksum())
     return FALSE;

   return TRUE;
}


void DcmInformation::setAttributes(int tag1, int tag2)
{
   DcmElement * element = NULL;
   if(this->getDataset()->findAndGetElement(DcmTagKey(tag1,tag2),element).bad())
     element = NULL;

   info.append(element);
}


QVector <DcmElement*> DcmInformation::getAttributes()
{
   setAttributes(0x0010,0x0020);
   setAttributes(0x0010,0x0010);
   setAttributes(0x0010,0x1010);
   setAttributes(0x0008,0x0020);
   setAttributes(0x0008,0x0023);

   return info;
}


BOOL DcmInformation::fileChecksum()
{
   OFCondition oc = this->validateMetaInfo(
       this->getDataset()->getOriginalXfer());
   //check the MetaInfo
   if(oc.bad())
     return TRUE;
   //check the dataset
   DcmElement *dcmElement = NULL;
   DcmTag dcmtag;
   int count = 0;

   while(TRUE)
   { //do foreach operation
     dcmElement = this->getDataset()->getElement(count++);
     dcmtag = dcmElement->getTag();
     //here do check data
     //..................

     if( "(7fe0,0010)" == QString(dcmtag.toString().c_str()))
      break;
   }

   return FALSE;
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


void DcmInformation::dcm2Xml(QString fileName,QString openfilepath)
{
   if(!openfilepath.isEmpty() && !this->getDataset()->isEmpty())
   {
//     if(fileName.endsWith(".dcm"))
     if(fileName.right(3).toLower() == "dcm")
       this->saveFile(fileName.toStdString().c_str());
//     if(fileName.endsWith(".xml"))
     if(fileName.right(3).toLower() == "xml")
     {
//      QXmlStreamReader xmlReader;
//       QFile file(fileName.toStdString().c_str());
//        if(!file.open(QIODevice::ReadWrite))
//            return false;
//        QTextStream out(&file);
//        out<<"<?xml version=\"1.0\" ?>\n";
//        file.close();
//       if(!file.open(QIODevice::ReadWrite))
//         return;
       std::ofstream myfile(fileName.toStdString().c_str());
       myfile<<"<?xml version=\"1.0\" ?>\n";
//       this->loadFile(openfilepath.toStdString().c_str());
       this->writeXML(myfile);
       myfile.close();
     }
   }
}
