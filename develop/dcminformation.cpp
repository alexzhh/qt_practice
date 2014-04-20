#include "dcminformation.h"

DcmInformation::DcmInformation(QString iPath, QString oPath)
{
  this->inputFilePath = iPath;
  this->outputFilePath = oPath;
}


DcmInformation::~DcmInformation()
{
}


bool DcmInformation::loadFromDCM()
{
   OFCondition oc = this->loadFile(this->inputFilePath.toStdString().c_str());

   if(oc.bad() || !isValid())
     return false;
    //errorMsg
   return true;
}


void DcmInformation::setAttributes(Uint16 GroupNum, Uint16 ElementNum)
{
   DcmElement * element = NULL;
   this->getDataset()->findAndGetElement(DcmTagKey(GroupNum, ElementNum), element);

   info.append(element);
}


QVector <DcmElement*> DcmInformation::getAttributes()
{
   info.clear();
   //clear the buffer
   setAttributes(0x0010,0x0020);
   setAttributes(0x0010,0x0010);
   setAttributes(0x0010,0x1010);
   setAttributes(0x0008,0x0020);
   setAttributes(0x0008,0x0023);

   return info;
}


QString DcmInformation::getStringlizeTag(const DcmTag& dcmtag)
{
   return dcmtag.toString().c_str();
}


bool DcmInformation::endOfDataSet(const DcmTag& dcmtag)
{
   return "(7fe0,0010)" == this->getStringlizeTag(dcmtag);
}


bool DcmInformation::isValid()
{
   OFCondition oc = this->validateMetaInfo(
       this->getDataset()->getOriginalXfer());
   //check the MetaInfo
   if(oc.bad())
     return false;
   //check the dataset
   DcmElement *dcmElement = NULL;
   DcmTag dcmtag;
   int count = 0;

   do
   { //do foreach operation
     dcmElement = this->getDataset()->getElement(count++);
     dcmtag = dcmElement->getTag();
     //here do check data
     //..................

   } while(!(this->endOfDataSet(dcmtag)));

   return true;
}


QString DcmInformation::getInputFile()
{
   return this->inputFilePath;
}


QString DcmInformation::getOutputFile()
{
   return this->outputFilePath;
}


void DcmInformation::setOutputFile(const QString &oPath)
{
   this->outputFilePath = oPath;
}


void DcmInformation::customSaveFile()
{
   if(!outputFilePath.isEmpty())
   {
     FileFliter FileType = this->getSavedFileType();
     switch(FileType)
     {
       case Type_DCM: // DCM
         this->saveDcmFile();
         break;
       case Type_XML: // XML
         this->saveXmlFile();
         break;
     }
   }
}


FileFliter DcmInformation::getSavedFileType()
{
   if(outputFilePath.toLower().endsWith(".dcm"))
     return Type_DCM;
   if(outputFilePath.toLower().endsWith(".xml"))
     return Type_XML;

   return Type_UNKNOW; //other
}


void DcmInformation::saveDcmFile()
{
   this->saveFile(outputFilePath.toStdString().c_str());
}


void DcmInformation::saveXmlFile()
{
   std::ofstream myfile(outputFilePath.toStdString().c_str());
   myfile<<"<?xml version=\"1.0\" ?>\n";
   //wirte Metainformation of xml
   this->writeXML(myfile);
   myfile.close();
}
