#include "dcminformation.h"

#define roundf(x) (int(x+0.5))


DcmInformation::DcmInformation(QString iPath, QString oPath)
{
  qimage = NULL;
  this->inputFilePath = iPath;
  this->outputFilePath = oPath;
  this->loaded = false;
}


DcmInformation::~DcmInformation()
{
  if(qimage != NULL)
    delete qimage;
}


bool DcmInformation::isLoaded() {
    return this->loaded;
}

bool DcmInformation::loadFromDCM()
{
   OFCondition oc = this->loadFile(this->inputFilePath.toStdString().c_str());

   if(oc.bad() || !isValid())
     return false;
    //errorMsg
   return true;
}

/*
bool DcmInformation::initial(QString OpenPath)
{
   OFCondition oc = this->loadFile(OpenPath.toStdString().c_str());

   if(oc.bad() || fileChecksum())
     return false;
    //errorMsg
   return true;
}

*/
void DcmInformation::setAttributes(int GroupNum, int ElementNum)
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

QString DcmInformation::getStringlizeTag(const DcmTag& dcmtag) {
    return QString(dcmtag.toString().c_str());
}

bool DcmInformation::endOfDataSet(const DcmTag& dcmtag) {
    return "(7fe0,0010)" == this->getStringlizeTag(dcmtag);
}

bool DcmInformation::isValid() {
    OFCondition oc = this->validateMetaInfo(
        this->getDataset()->getOriginalXfer());
    //check the MetaInfo
    if(oc.bad())
      return false;
    //check the dataset
    DcmElement *dcmElement = NULL;
    DcmTag dcmtag;
    int count = 0;


    do { //do foreach operation
      dcmElement = this->getDataset()->getElement(count++);
      dcmtag = dcmElement->getTag();
      //here do check data
      //..................
     } while(!(this->endOfDataSet(dcmtag)));

     return true;
}

/*
bool DcmInformation::fileChecksum()
{
   OFCondition oc = this->validateMetaInfo(
       this->getDataset()->getOriginalXfer());
   //check the MetaInfo
   if(oc.bad())
     return true;
   //check the dataset
   DcmElement *dcmElement = NULL;
   DcmTag dcmtag;
   int count = 0;


   do { //do foreach operation
     dcmElement = this->getDataset()->getElement(count++);
     dcmtag = dcmElement->getTag();
     //here do check data
     //..................
    } while(!(this->endOfDataSet(dcmtag)));

    return false;
}
*/

QPixmap DcmInformation::drawDcmImage(int width, int height)
{
   E_TransferSyntax transf = this->getDataset()->getOriginalXfer();
   DicomImage dicom( this->getDataset(),
                     transf,
                     CIF_AcrNemaCompatibility, 0, 1);
   int dimgWidth = dicom.getWidth();
   int dimgHeight = dicom.getHeight();

   if(dicom.isMonochrome())
   {
     if(qimage != NULL)
       delete qimage;
     qimage = new QImage(dimgWidth,dimgHeight,QImage::Format_Indexed8);
   }
   else
   {
     if(qimage != NULL)
       delete qimage;
     qimage = new QImage(dimgWidth,dimgHeight,QImage::Format_ARGB32);
   }

   const DiPixel* diPixel = dicom.getInterData();
   if(dicom.isMonochrome())
   {
     switch(diPixel->getRepresentation())
     {
      case EPR_Sint8:
       {
         const char* pixelData = (const char*)diPixel->getData();
         MonochromeColorTrans(pixelData);break;
       }
      case EPR_Uint8:
       {
         const uchar* pixelData = (const uchar*)diPixel->getData();
         MonochromeColorTrans(pixelData);break;
       }
      case EPR_Sint16:
       {
         const short* pixelData = (const short*)diPixel->getData();
         MonochromeColorTrans(pixelData);break;
       }
      case EPR_Uint16:
       {
         const ushort* pixelData = (const ushort*)diPixel->getData();
         MonochromeColorTrans(pixelData);break;
       }
      case EPR_Sint32:
       {
         const int* pixelData = (const int*)diPixel->getData();
         MonochromeColorTrans(pixelData);break;
       }
      case EPR_Uint32:
       {
         const uint* pixelData = (const uint*)diPixel->getData();
         MonochromeColorTrans(pixelData);break;
       }
     }
   }
   else
   {
     const uchar* pixelData = (const uchar*) diPixel->getData();
     int qimgWidth  = qimage->width();
     int qimgHeight = qimage->height();

     uchar *qImageBuffer = qimage->bits();
     uchar colorPixel = NULL;
     for(long pixels = qimgWidth*qimgHeight; pixels!=0; pixels--)
     {
       colorPixel = colorPalette(*pixelData++);
       *qImageBuffer++ = colorPixel; //R
       *qImageBuffer++ = colorPixel; //G
       *qImageBuffer++ = colorPixel; //B
       *qImageBuffer++ = 0XFF;   //Alpha
     }
   }

   return QPixmap::fromImage( *qimage).scaled(
     ((dimgWidth <= width) ? dimgWidth : width ),
     ((dimgHeight <= height) ? dimgHeight : height));
}

template <typename T>
void DcmInformation::MonochromeColorTrans(const T *pixelData)
{
   int qimgWidth  = qimage->width();
   int qimgHeight = qimage->height();

   for(int height=0; height < qimgHeight; height++)
   {
     uchar* scanLine = qimage->scanLine(height);
     for(int width=0; width < qimgWidth; width++)
     {
       *scanLine++ = colorPalette(*pixelData++);
     }
   }
}


uchar DcmInformation::colorPalette(float value)
{
   float color = (value - 512)/1024 *255.0 + 127.5 ;
   if(color < 0.0)
     return 0.0;
   else if(color > 255.0)
     return 255.0;
   else
     return (uchar)(roundf(color));
}

QString DcmInformation::getInuptFile() {
    return this->inputFilePath;
}

void DcmInformation::setOutputFile(QString oPath) {
    this->outputFilePath = oPath;
}

void DcmInformation::customSaveFile() {
    int FileType = this->getSavedFileType();
    if(!outputFilePath.isEmpty() && !this->getDataset()->isEmpty()) {
        switch(FileType) {
            case 0: // DCM
                this->saveDcmFile();
                break;
            case 1: // XML
                this->saveXmlFile();
                break;
        }
     }
}

int DcmInformation::getSavedFileType() {
    if(outputFilePath.toLower().endsWith(".dcm"))
        return 0;
    if(outputFilePath.toLower().endsWith(".xml"))
        return 1;
}

void DcmInformation::saveDcmFile() {

      this->saveFile(outputFilePath.toStdString().c_str());
}

void DcmInformation::saveXmlFile() {
      std::ofstream myfile(outputFilePath.toStdString().c_str());
      myfile<<"<?xml version=\"1.0\" ?>\n";
      this->writeXML(myfile);
      myfile.close();
}

/*
void DcmInformation::dcm2Xml()
{
   if(!outputFilePath.isEmpty() && !this->getDataset()->isEmpty())
   {

     if(outputFilePath.toLower().endsWith(".dcm"))
       this->saveFile(outputFilePath.toStdString().c_str());
     if(outputFilePath.toLower().endsWith(".xml"))
     {
       std::ofstream myfile(outputFilePath.toStdString().c_str());
       myfile<<"<?xml version=\"1.0\" ?>\n";
       this->writeXML(myfile);
       myfile.close();
     }
   }

}
*/
