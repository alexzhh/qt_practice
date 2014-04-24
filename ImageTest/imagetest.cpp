#include <QString>
#include <QtTest>
#include "../../QTPractice/imageview.h"
Q_DECLARE_METATYPE(QImage::Format)
Q_DECLARE_METATYPE(EP_Representation)

class QTtest : public QObject
{
    Q_OBJECT
private:
    ImageView *imageview;

public:
    QTtest();

private Q_SLOTS:
    void cleanupQTtestTest();
    void testStructure();
    void testLoadDcmFile();
    void testInitMapContainer();
    void testInitMapContainer_data();
    void testColorPalette();
    void testColorPalette_data();
    void testDrawMonochromeAlux();
    void testDrawRGBAlux();
    void testMonochromeColorTrans();
    void testDrawMonochrome();
    void testDrawRGB();
    void testDrawDcmImage();
    void testDrawDcmImage_data();
    void testDrawMonochromeAluxNeg();
    void testDrawMonochromeAluxNeg_data();
    void testMonochromeColorTransNeg();
    void testMonochromeColorTransNeg_data();
    void testDrawDcmImageNeg();
    void testDrawDcmImageNeg_data();
    void testInitMapContainerNeg();
    void testInitMapContainerNeg_data();
    void testLoadDcmFileNeg();
};

QTtest::QTtest()
{
}

void QTtest::cleanupQTtestTest()
{
   if(imageview != NULL)
     delete imageview;
}

void QTtest::testDrawMonochrome()
{
   imageview->drawMonochrome();
   QCOMPARE(imageview->getImage()->format(),QImage::Format_Indexed8);
   QCOMPARE(imageview->getImage()->isNull(), false);
}

void QTtest::testDrawRGB()
{
   imageview->drawRGB();
   QCOMPARE(imageview->getImage()->format(),QImage::Format_ARGB32);
   QCOMPARE(imageview->getImage()->isNull(), false);
}

void QTtest::testDrawDcmImage()
{
   QFETCH(QImage::Format, testFormat);
   QFETCH(QImage::Format, Format);
   QFETCH(bool, testBits);
   QFETCH(bool, Bits);
   QCOMPARE(testFormat, Format);
   QCOMPARE(testBits, Bits);
}
void QTtest::testDrawDcmImageNeg()
{
   QFETCH(QImage::Format, testFormat);
   QFETCH(QImage::Format, Format);
   QFETCH(bool, testBits);
   QFETCH(bool, Bits);
   QVERIFY(testFormat != Format);
   QCOMPARE(testBits, Bits);
}

void QTtest::testDrawDcmImage_data()
{
   QTest::addColumn<QImage::Format>("testFormat");
   QTest::addColumn<QImage::Format>("Format");
   QTest::addColumn<bool>("testBits");
   QTest::addColumn<bool>("Bits");
   imageview->drawMonochrome();
   QTest::newRow("Monochrome")<<imageview->getImage()->format()
                       <<QImage::Format_Indexed8
                       <<imageview->getImage()->isNull()
                       <<false;
   imageview->drawRGB();
   QTest::newRow("RGB")<<imageview->getImage()->format()
                       <<QImage::Format_ARGB32
                       <<imageview->getImage()->isNull()
                       <<false;
}

void QTtest::testDrawDcmImageNeg_data()
{
   QTest::addColumn<QImage::Format>("testFormat");
   QTest::addColumn<QImage::Format>("Format");
   QTest::addColumn<bool>("testBits");
   QTest::addColumn<bool>("Bits");
   imageview->drawMonochrome();
   QTest::newRow("Invalid")<<imageview->getImage()->format()
                       <<QImage::Format_Invalid
                       <<imageview->getImage()->isNull()
                       <<false;
   imageview->drawRGB();
   QTest::newRow("Mono")<<imageview->getImage()->format()
                       <<QImage::Format_Mono
                       <<imageview->getImage()->isNull()
                       <<false;
}

void QTtest::testDrawMonochromeAlux()
{
   const DiPixel* diPixel = imageview->getDicomImage()->getInterData();
   EP_Representation type = diPixel->getRepresentation();
   QCOMPARE(type, EPR_Sint16);
}

void QTtest::testDrawMonochromeAluxNeg()
{
   QFETCH(EP_Representation, testValue);
   QFETCH(EP_Representation, Value);
   QVERIFY(testValue != Value);

}

void QTtest::testDrawMonochromeAluxNeg_data()
{
   QTest::addColumn<EP_Representation>("testValue");
   QTest::addColumn<EP_Representation>("Value");
   const DiPixel* diPixel = imageview->getDicomImage()->getInterData();
   EP_Representation type = diPixel->getRepresentation();
   QTest::newRow("EPR_Sint8")<<type<<EPR_Sint8;
   QTest::newRow("EPR_Uint8")<<type<<EPR_Uint8;
   QTest::newRow("EPR_Uint16")<<type<<EPR_Uint16;
   QTest::newRow("EPR_Sint32")<<type<<EPR_Sint32;
   QTest::newRow("EPR_Uint32")<<type<<EPR_Uint32;
}

void QTtest::testDrawRGBAlux()
{
   imageview->drawRGBAlux();
   QCOMPARE(imageview->getImage()->isNull(),false);
}

void QTtest::testMonochromeColorTrans()
{
   const DiPixel* diPixel = imageview->getDicomImage()->getInterData();
   const short* pixelData_short = (const short*)diPixel->getData();
   imageview->MonochromeColorTrans(pixelData_short);
   QCOMPARE(diPixel->getRepresentation(), EPR_Sint16);
   QCOMPARE(imageview->getImage()->isNull(), false);
}

void QTtest::testMonochromeColorTransNeg()
{
   QFETCH(EP_Representation, testEP_Rp);
   QFETCH(EP_Representation, EP_Rp);
   QFETCH(bool, testBits);
   QFETCH(bool, Bits);
   QVERIFY(testEP_Rp != EP_Rp);
   QVERIFY(testBits != Bits);
}

void QTtest::testMonochromeColorTransNeg_data()
{
   QTest::addColumn<EP_Representation>("testEP_Rp");
   QTest::addColumn<EP_Representation>("EP_Rp");
   QTest::addColumn<bool>("testBits");
   QTest::addColumn<bool>("Bits");
   const DiPixel* diPixel = imageview->getDicomImage()->getInterData();
   EP_Representation type = diPixel->getRepresentation();
   const uchar* pixelData_uchar = (const uchar*)diPixel->getData();
   imageview->MonochromeColorTrans(pixelData_uchar);
   QTest::newRow("EPR_Uint8")<<type<<EPR_Sint8<<imageview->getImage()->isNull()<<true;
   const char* pixelData_char = (const char*)diPixel->getData();
   imageview->MonochromeColorTrans(pixelData_char);
   QTest::newRow("EPR_Sint8")<<type<<EPR_Uint8<<imageview->getImage()->isNull()<<true;
   const ushort* pixelData_ushort = (const ushort*)diPixel->getData();
   imageview->MonochromeColorTrans(pixelData_ushort);
   QTest::newRow("EPR_Uint16")<<type<<EPR_Uint16<<imageview->getImage()->isNull()<<true;
}

void QTtest::testStructure()
{
   imageview = new ImageView();
   QVERIFY(imageview->getDicomImage() == NULL);
   QVERIFY(imageview->getImage() == NULL);
   QCOMPARE(imageview->getImageHeight(), 0);
   QCOMPARE(imageview->getImageWidth(), 0);
}

void QTtest::testLoadDcmFile()
{
   QString cPath = "../../CodeTest/CT.dcm";
   QCOMPARE(imageview->loadDcmFile(cPath),true);
   QVERIFY(imageview->getDicomImage() != NULL);
   QVERIFY(imageview->getImage() == NULL);
   QVERIFY(imageview->getImageHeight() != 0);
   QVERIFY(imageview->getImageWidth() != 0);
}

void QTtest::testLoadDcmFileNeg()
{
//   QString wPath = "../../CodeTest/1.dcm";
//   QCOMPARE(imageview->loadDcmFile(wPath),false);
}

void QTtest::testInitMapContainer()
{
   QFETCH(QImage::Format, testValue);
   QFETCH(QImage::Format, Value);
   QCOMPARE(testValue, Value);
}

void QTtest::testInitMapContainerNeg()
{
   QFETCH(QImage::Format, testValue);
   QFETCH(QImage::Format, Value);
   QCOMPARE(testValue, Value);
}

void QTtest::testInitMapContainerNeg_data()
{
   QTest::addColumn<QImage::Format>("testValue");
   QTest::addColumn<QImage::Format>("Value");
   imageview->initMapContainer(QImage::Format_Invalid);
   QTest::newRow("Format_Invalid")<<imageview->getImage()->format()
                                   <<QImage::Format_Invalid;
   imageview->initMapContainer(QImage::Format_Mono);
   QTest::newRow("Format_Mono")<<imageview->getImage()->format()
                                   <<QImage::Format_Mono;
}

void QTtest::testInitMapContainer_data()
{
   QTest::addColumn<QImage::Format>("testValue");
   QTest::addColumn<QImage::Format>("Value");
   imageview->initMapContainer(QImage::Format_Indexed8);
   QTest::newRow("Format_Indexed8")<<imageview->getImage()->format()
                                   <<QImage::Format_Indexed8;
   imageview->initMapContainer(QImage::Format_ARGB32);
   QTest::newRow("Format_ARGB32")<<imageview->getImage()->format()
                                 <<QImage::Format_ARGB32;
}

void QTtest::testColorPalette()
{
   QFETCH(uchar,testValue);
   QFETCH(uchar, Value);
   QCOMPARE(testValue, Value);
}

void QTtest::testColorPalette_data()
{
   QTest::addColumn<uchar>("testValue");
   QTest::addColumn<uchar>("Value");
   QTest::newRow("Less than 0")<<imageview->colorPalette(-20)<<(uchar)0;
   QTest::newRow("Between 0 and 255")<<imageview->colorPalette(20)<<(uchar)5;
   QTest::newRow("More than 255")<<imageview->colorPalette(2000)<<(uchar)255;
}



QTEST_APPLESS_MAIN(QTtest)

#include "imagetest.moc"
