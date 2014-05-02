#include "dcminformation.h"

DcmInformation::DcmInformation(QString iPath, QString oPath)
{
  this->inputFilePath = iPath;
  this->outputFilePath = oPath;

  setAttributes();
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


void DcmInformation::setAttributes()
{
   Elementinfo annotation[5];
   fromCfgTag.clear();
   annotation[0].GTag = 0x0010; annotation[0].ETag = 0x0020;
   annotation[0].TagName = "PatientID";
   annotation[0].EVR = EVR_LO;
   annotation[1].GTag = 0x0010; annotation[1].ETag = 0x0010;
   annotation[1].TagName = "PatientName";
   annotation[1].EVR = EVR_PN;
   annotation[2].GTag = 0x0010; annotation[2].ETag = 0x1010;
   annotation[2].TagName = "PatientAge";
   annotation[2].EVR = EVR_AS;
   annotation[3].GTag = 0x0008; annotation[3].ETag = 0x0020;
   annotation[3].TagName = "StudyDate";
   annotation[3].EVR = EVR_DA;
   annotation[4].GTag = 0x0008; annotation[4].ETag = 0x0023;
   annotation[4].TagName = "ContentDate";
   annotation[4].EVR = EVR_DA;
   for(int i=0;i<5;++i)
    fromCfgTag.push_back(annotation[i]);
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


Elementinfo DcmInformation::findTagFromTagName(const QString tagname)
{
   foreach(Elementinfo ele,fromCfgTag)
   {
     if(tagname == ele.TagName)
       return ele;
   }
}


QString DcmInformation::getStringlizeTag(const DcmTag& dcmtag)
{
   return dcmtag.toString().c_str();
}


bool DcmInformation::endOfDataSet(const DcmTag& dcmtag)
{
   return "(7fe0,0010)" == this->getStringlizeTag(dcmtag);
}


bool DcmInformation::checkEachTag(const QString tagname, const char *value)
{
   Elementinfo eletag = findTagFromTagName(tagname);
   return checkEachTag(eletag.EVR, value);
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
     return drawImage.drawDcmImage(QPixmap(),width,height);
   return QPixmap();
}


void DcmInformation::putAndInsertString(const QString tagname, const QString& value)
{
   Elementinfo eletag = findTagFromTagName(tagname);
   this->getDataset()->putAndInsertString(DcmTagKey(eletag.GTag,eletag.ETag),
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
