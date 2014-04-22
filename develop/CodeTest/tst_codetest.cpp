#include <QString>
#include <QtTest>
#include "dcminformation.h"

class CodeTest : public QObject
{
    Q_OBJECT

public:
    CodeTest();

private:
    DcmInformation *testDcm;

private Q_SLOTS:
    void testStructure();
    void cleanupTestCase();
    void testloadFromDCM();
    void testgetStringlizeTag();
    void testendOfDataSet();
    void testisisValid();
    void testcustomSaveFile();
    void testgetSavedFileType();
    void testsaveDcmFile();
    void testsaveXmlFile();
    void testgetAttributes();
    void testgetAttributes_data();
    void testsetOutputFile();
    void testgetInputFile();
    void testgetOutputFile();
    void testdrawDcmImage();
    void testputAndInsertString();
    void testcheckEachTag();
};

//构造和回收函数
CodeTest::CodeTest()
{
}

void CodeTest::cleanupTestCase()
{
    delete testDcm;
}


//测试函数的实现

void CodeTest::testStructure()
{
    QString testiPath="e://CT.dcm";
    QString testoPath="";
    testDcm=new DcmInformation(testiPath,testoPath);
    QCOMPARE(testDcm->getInputFile(),QString("e://CT.dcm"));
    QCOMPARE(testDcm->getOutputFile(),QString(""));

}


void CodeTest::testloadFromDCM()
{

   QCOMPARE(testDcm->loadFromDCM(),true);


}



void CodeTest::testgetStringlizeTag()
{
      DcmElement *testDcmElement;
      testDcm->getDataset()->findAndGetElement(DCM_PatientName,testDcmElement);
      QString testString=QString(testDcm->getStringlizeTag(testDcmElement->getTag()));
      QCOMPARE(testString,QString("(0010,0010)"));
}

void CodeTest::testendOfDataSet()
{
    DcmElement *testDcmElement;
    testDcm->getDataset()->findAndGetElement(DCM_PatientName,testDcmElement);
    QCOMPARE(testDcm->endOfDataSet(testDcmElement->getTag()),false);

}



void CodeTest::testisisValid()
{

    QCOMPARE(testDcm->isValid(),true);

}

//暂定测试
void CodeTest::testcustomSaveFile()
{




}


void CodeTest::testgetSavedFileType()
{
    QCOMPARE(testDcm->getSavedFileType(),Type_UNKNOW);
}

void CodeTest::testsetOutputFile()
{
    QString testString="e://1.dcm";
    testDcm->setOutputFile(testString);
    QCOMPARE(testDcm->getOutputFile(),testString);


}


//暂不测试
void CodeTest::testsaveDcmFile()
{



}

//暂不测试
void CodeTest::testsaveXmlFile()
{



}


void CodeTest::testgetAttributes()
{

        testDcm->getAttributes();
        QFETCH(QString,value);
        QFETCH(QString,testvalue);
        QCOMPARE(testvalue,value);
}


void CodeTest::testgetAttributes_data()
{
     OFString testvalue_tmp;
     QTest::addColumn<QString>("testvalue");
     QTest::addColumn<QString>("value");
     testDcm->getDataset()->findAndGetOFString(DCM_PatientID,testvalue_tmp);
     QTest::newRow("1")<<QString(testvalue_tmp.c_str())<<"000484";
     testDcm->getDataset()->findAndGetOFString(DCM_PatientName ,testvalue_tmp);
     QTest::newRow("2")<<QString(testvalue_tmp.c_str())<<"GGGGG AAAAA BBBB";
     testDcm->getDataset()->findAndGetOFString(DCM_PatientAge ,testvalue_tmp);
     QTest::newRow("3")<<QString(testvalue_tmp.c_str())<<"060Y";
     testDcm->getDataset()->findAndGetOFString(DCM_StudyDate ,testvalue_tmp);
     QTest::newRow("4")<<QString(testvalue_tmp.c_str())<<"20090207";
     testDcm->getDataset()->findAndGetOFString(DCM_StudyTime,testvalue_tmp);
     QTest::newRow("5")<<QString(testvalue_tmp.c_str())<<"094634.000";

}

void CodeTest::testgetInputFile()
{

   QCOMPARE(testDcm->getInputFile(),QString("e://CT.dcm"));

}

void CodeTest::testgetOutputFile()
{

   QCOMPARE(testDcm->getOutputFile(),QString("e://1.dcm"));

}

//牵扯到imageview类  暂不测试
void CodeTest::testdrawDcmImage()
{


}



void CodeTest::testputAndInsertString()
{
    //这里输入了正确的值与错误的对比了
    OFString testvalue_tmp;
    QString testString="ABC";
    //testDcm->putAndInsertString(0x0010,0x0010,testString);
    testDcm->getDataset()->findAndGetOFString(DCM_PatientName ,testvalue_tmp);
    //QCOMPARE(QString(testvalue_tmp.c_str()),testString);
    testDcm->putAndInsertString(0x0010,0x0010,QString("GGGGG AAAAA BBBB"));
    QCOMPARE(QString(testvalue_tmp.c_str()),testString);

}


void CodeTest::testcheckEachTag()
{

    int testintvalue;
    const int & testvalue=testintvalue;
    testintvalue=12;
    bool testboolvalue=testDcm->checkEachTag(testvalue,NULL);
    QCOMPARE(testboolvalue,true);


}



QTEST_APPLESS_MAIN(CodeTest)

#include "tst_codetest.moc"
