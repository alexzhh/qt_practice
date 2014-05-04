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


QMap <QString, QPair<ushort, ushort> > DcmInformation::getAttributes(const QList<QString> &tagname)
{
   QMap <QString, QPair<ushort, ushort> > annotation;
   DcmElement * dcmElement = NULL;
   DcmTag dcmtag;
   int index = 0;
   int count = 0;
   do
   {
     dcmElement = this->getDataset()->getElement(count++);
     dcmtag = dcmElement->getTag();
     if((index = tagname.indexOf(dcmtag.getTagName())) != -1)
     {
       QPair<ushort, ushort> tag;
       tag.first = dcmtag.getGTag();
       tag.second = dcmtag.getETag();
       annotation.insert(tagname.at(index),tag);
     }
   } while(!(this->endOfDataSet(dcmtag)));

   return annotation;
}


QString DcmInformation::getDcmQStringValue(ushort gtag, ushort etag)
{
   DcmElement * element = NULL;
   OFString ofstr = "";
   this->getDataset()->findAndGetElement(DcmTagKey(gtag, etag), element);
   if(element == NULL)
     return "";

   element->getOFString(ofstr,0);
   return ofstr.c_str();
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
   QList<QString> tagnamelist;
   tagnamelist.append(tagname);
   QMap <QString, QPair<ushort, ushort> > attr = this->getAttributes(tagnamelist);
   if(!attr.isEmpty())
   {
     QPair<ushort, ushort> tag = attr.value(tagname);
     return checkEachTag(tag.first, tag.second, value);
   }

   //return false;
   //May produce an error when the searched dcmtagkey isn't in dataset
   return true;

}


bool DcmInformation::checkEachTag(ushort gtag, ushort etag, const char * value)
{
   DcmElement * element = NULL;
   this->getDataset()->findAndGetElement(DcmTagKey(gtag, etag), element);
   if(element != NULL)
     return checkEachTag(element->getVR(), value);
   else
     return false;
}


bool DcmInformation::checkEachTag(const DcmEVR &dcmevr, const char *value)
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


bool DcmInformation::putAndInsertString(const QString tagname, const QString& value)
{
   QList<QString> tagnamelist;
   tagnamelist.append(tagname);
   QMap <QString, QPair<ushort, ushort> > attr = this->getAttributes(tagnamelist);
   if(!attr.isEmpty())
   {
     QPair<ushort, ushort> tag = this->getAttributes(tagnamelist).value(tagname);
     return putAndInsertString(tag.first, tag.second, value);
   }

   return false;
}


bool DcmInformation::putAndInsertString(ushort gtag, ushort etag, const QString& value)
{
   return this->getDataset()->putAndInsertString(DcmTagKey(gtag,etag),
                                  value.toStdString().c_str()).good();
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


bool DcmInformation::saveDcmFile()
{
   return this->saveFile(outputFilePath.toStdString().c_str()).good();
}


bool DcmInformation::saveXmlFile()
{
   std::ofstream myfile(outputFilePath.toStdString().c_str());
   myfile<<"<?xml version=\"1.0\" ?>\n";
   //wirte Metainformation of xml
   OFCondition oc = this->writeXML(myfile);
   myfile.close();
   return oc.good();
}
