#include "imageview.h"

ImageView::ImageView()
  :qimage(NULL),dicomImage(NULL)
  ,imageWidth(0),imageHeight(0)
{
}

ImageView::~ImageView()
{
   if(qimage != NULL)
     delete qimage;
   if(dicomImage != NULL)
     delete dicomImage;
}

bool ImageView::loadDcmFile(QString oPath)
{
   if(dicomImage != NULL)
     delete dicomImage;
   dicomImage = new DicomImage(oPath.toStdString().c_str());
   if(dicomImage != NULL && dicomImage->getStatus() == EIS_Normal)
   {
     imageWidth = dicomImage->getWidth();  //set image width
     imageHeight = dicomImage->getHeight();//set image height
     return true;
   }
    //errorMsg
   return false;
}


QPixmap ImageView::drawDcmImage(int width, int height)
{
   if(dicomImage->isMonochrome())
      this->drawMonochrome(); // draw Monochrome picture
   else
      this->drawRGB();      // draw RGB picture

   return QPixmap::fromImage( *qimage).scaled(
     (imageWidth <= width ? imageWidth : width),
     (imageHeight <= height ? imageHeight : height));
    // get mininum width and height, scale the picture
}


void ImageView::drawMonochromeAlux()
{
    const DiPixel* diPixel = dicomImage->getInterData();
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


void ImageView::drawRGBAlux()
{
   const DiPixel* diPixel = dicomImage->getInterData();
   const uchar* pixelData = (const uchar*) diPixel->getData();

   uchar *qImageBuffer = qimage->bits();
   //get image buffer
   uchar colorPixel = NULL;
   for(long pixels = imageWidth*imageHeight; pixels!=0; pixels--)
    {
      colorPixel = colorPalette(*pixelData++);
      *qImageBuffer++ = colorPixel; //R
      *qImageBuffer++ = colorPixel; //G
      *qImageBuffer++ = colorPixel; //B
      *qImageBuffer++ = 0XFF;   //Alpha
    }

}


void ImageView::initMapContainer(QImage::Format FormatType)
{
   if(qimage != NULL)
     delete qimage;
   qimage = new QImage(imageWidth,imageHeight,FormatType);
}


void ImageView::drawMonochrome()
{
   initMapContainer(QImage::Format_Indexed8);//Monochrome
   drawMonochromeAlux();
}


void ImageView::drawRGB()
{
   initMapContainer(QImage::Format_ARGB32);//RGB
   drawRGBAlux();
}


template <typename T>
void ImageView::MonochromeColorTrans(const T *pixelData)
{
   for(int height=0; height < imageHeight; height++)
   {
     uchar* scanLine = qimage->scanLine(height);
     for(int width=0; width < imageWidth; width++)
     {
       *scanLine++ = colorPalette(*pixelData++);
     }
   }
}


uchar ImageView::colorPalette(float value)
{
   float color = (value - 512)/1024 *255.0 + 127.5 ;
   if(color < 0.0)
     return 0.0;
   else if(color > 255.0)
     return 255.0;
   else
     return (uchar)(roundf(color)); //rounding
}
