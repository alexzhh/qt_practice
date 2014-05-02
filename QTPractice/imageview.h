#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QPicture>

#define roundf(x) (int(x+0.5))

class ImageView
{
private:
    QImage * qimage;
    DicomImage *dicomImage;
    int imageWidth;  // image width
    int imageHeight; // image height
public:
    ImageView();
    ~ImageView();

    QImage* getImage();//return image object
    DicomImage* getDicomImage();//return dicomImage object
    int getImageWidth();//return image width
    int getImageHeight();//return image height
    bool loadDcmFile(QString oPath);
    // load DCM data from *.dcm
    QImage  drawDcmImage(int width, int height);
    //draw image return QImage
    QPixmap drawDcmImage(QPixmap img, int width, int height);
    //draw image return QPixmap
    QBitmap drawDcmImage(QBitmap img, int width, int height);
    //draw image return QBitmap
//    QPicture drawDcmImage(QPicture  img, int width, int height);
    void renderImage();
    //draw Monochrome picture or RGB picture
    void scaleDcmImage(const int & width, const int & height);
    //scale the picture from dicomImage;
    void rotaterDcmImage(const double degree);
    //rotate the picture from dicomImage(any angle);
    template <typename T>  //c++ template
    void MonochromeColorTrans(const T *pixelData);
    //Assign pixel stream(Monochrome) to qimage bits
    uchar colorPalette(float value);
    //adjust the color of slate according to(center-window,width,value)
    void drawMonochrome();
    //draw Monochrome(init qimage map and get pixel stream)
    void drawMonochromeAlux();
    //get pixel stream(Monochrome) from DicomImage
    void drawRGB();
    //draw RGB(init qimage map and get pixel stream)
    void drawRGBAlux();
    //Assign pixel stream(RGB) to qimage bits
    void initMapContainer(QImage::Format FormatType);
    //initialize qimage map(Format_Indexed8 or Format_ARGB32)
};

#endif // IMAGEVIEW_H
