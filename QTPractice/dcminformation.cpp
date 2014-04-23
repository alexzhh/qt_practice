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


bool DcmInformation::checkEachTag(const int &dcmevr, const char *value)
{
   bool flag = true;
   switch(dcmevr)
   {
     case EVR_OB://12
     case EVR_OF://13
     case EVR_OW://14
     case EVR_SQ://18
       break;
     case EVR_AT://2
     case EVR_FL://7
     case EVR_FD://8
     case EVR_SL://17
     case EVR_SS://19
     case EVR_UL://23
     case EVR_US://24
//        if(DcmElement::checkVM(dcmElement->getVM(), "1-n").bad()) flag = false;
       break;
     case EVR_AE://0
        if(DcmApplicationEntity::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_AS://1
        if(DcmAgeString::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_CS://3
        if(DcmCodeString::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_DA://4
        if(DcmDate::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_DS://5
        if(DcmDecimalString::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_DT://6
        if(DcmDateTime::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_IS://9
        if(DcmIntegerString::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_LO://10
        if(DcmLongString::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_LT://11
        if(DcmLongText::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_PN://15
        if(DcmPersonName::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_SH://16
        if(DcmShortString::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_ST://20
        if(DcmShortText::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_TM://21
        if(DcmTime::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_UI://22
        if(DcmUniqueIdentifier::checkStringValue(value).bad()) flag = false;
       break;
     case EVR_UT://25
        if(DcmUnlimitedText::checkStringValue(value).bad()) flag = false;
       break;
     default:
        flag = false;
     }
   return flag;
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
   OFString value = "";
   int count = 0;

   do
   { //do foreach operation
     dcmElement = this->getDataset()->getElement(count++);
     dcmtag = dcmElement->getTag();
     //here do check data
     dcmElement->getOFString(value,0);
     if(!checkEachTag(dcmtag.getEVR(), value.c_str()))
        return false;

   } while(!(this->endOfDataSet(dcmtag)));

   return true;
}


QPixmap DcmInformation::drawDcmImage(int width, int height)
{
   ImageView drawImage;
   if(drawImage.loadDcmFile(this->inputFilePath))
     return drawImage.drawDcmImage(width,height);
   else
     return NULL; //error
}


void DcmInformation::putAndInsertString(Uint16 group, Uint16 element, const QString &value)
{
   this->getDataset()->putAndInsertString(DcmTagKey(group,element),
                                      value.toStdString().c_str());
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
