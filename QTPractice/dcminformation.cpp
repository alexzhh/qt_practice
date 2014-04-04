#include "dcminformation.h"


DcmInformation::DcmInformation()
{

}


DcmInformation::~DcmInformation()
{

}


void DcmInformation::openDcmFile(QString path)
{
   DcmFileFormat fileformat;
   OFCondition oc = fileformat.loadFile( path.toStdString().c_str());
   if(oc.good())
     data = *fileformat.getDataset();
   else
   {
     //errorMessage
   }
}


DcmDataset DcmInformation::getDcmData()
{
   return data;
}


void DcmInformation::setAttributes(int tag1, int tag2, int num)
{
   DcmElement * element;
   OFString ofstr;
   AttrElements attres;

   if( data.findAndGetElement(DcmTagKey(tag1,tag2),element).good())
   {
     attres.type = num;
     attres.vr = element->getTag().getVRName();
     element->getOFString(ofstr,0);
     attres.value = QString::fromStdString(ofstr.c_str());
     if(tag1==0x0008)
     {
       if( data.findAndGetElement(DcmTagKey(tag1,tag2 + 0x0010),element).good())
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


void DcmInformation::fileChecksum()
{

}


QPixmap DcmInformation::drawDcmImage(QString path)
{
//  DicomImage dicomimage(filename.toStdString().c_str());
//  const DiPixel* decompressedPixels = dicomimage.getInterData();
//  const uchar* indata = (const uchar*) decompressedPixels->getData();
//  QImage* renderedQImage = NULL;
// // data->findAndGetElement(DCM_PixelData,element);
//  int width, height;
//  width = dicomimage.getWidth();
//  height = dicomimage.getHeight();
//  //creat the internal QImage object
//  if(renderedQImage == NULL)
//  {
//      renderedQImage = new QImage(width,height, QImage::Format_ARGB32);
//  }

//  if(dicomimage.isMonochrome())
//   {
//    const char* indata = (const char*) decompressedPixels->getData();
//    mapMonochromeDICOMImageToQImage(indata, renderedQImage);
//   }
//  QImage(indata,width,height);
//  return QPixmap::fromImage( QImage(indata,width,height,QImage::Format_ARGB32));

    DcmFileFormat dfile ;
    OFCondition cond = dfile.loadFile(path.toStdString().c_str());
    E_TransferSyntax xfer = dfile.getDataset()->getOriginalXfer();
    DicomImage di(&dfile, xfer,CIF_AcrNemaCompatibility, 0, 1);

    di.setWindow(512,1024);
//    di.writeBMP("c:\\from_dicom.bmp",8);

//    const DiPixel* decompressedPixels = di.getInterData();
//    const uchar* indata = (const uchar*) decompressedPixels->getData();

//    int width, height;
//      width = di.getWidth();
//      height = di.getHeight();

    QImage im(di.getWidth(),di.getHeight(),QImage::Format_ARGB32);


//    int width = im.width();
//    int height = im.height();
//    for(int i = 0 ; i < height ; i++)
//    {
//        uchar* out = im.scanLine(i);


//        for(int j = 0 ; j < width ; j++)
//        {
//            float invalue = *(indata + i*width + j);
//            float color = (invalue - 217)/512 *255.0+127.5;
//            if(color < 0.0)
//                color = 0.0;
//            else if (color > 255.0)
//                color = 255.0;
//            uchar ucolor = (uchar) roundf(color);

//            *out++ = ucolor; //R
//            *out++ = ucolor; //G
//            *out++ = ucolor; //B
//            *out++ = 0xff; //A

//        }
//    }

    return QPixmap::fromImage(im);
    // return NULL;
}
