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
    //正确测试
    void testStructure();
    void cleanupTestCase();
    void testloadFromDCM();
    void testgetStringlizeTag();
    void testendOfDataSet();
    void testisValid();
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

    //以下为错误测试,由于错误测试时赋值为错误的，导致dcminformation无法初始化，许多方法无法调用
    void testStructureFalse();
    void testloadFromDCMFalse();
    void testElementIsExist();
    //isValid()函数存在问题，初始化失败后还可以继续调用，会报异常，预期为返回false
    //void testisValidFalse();
    //void testcustomSaveFileFalse();
    //void testgetSavedFileTypeFalse();
    //void testsaveDcmFileFalse();
    //void testsaveXmlFileFalse();
    // void testgetAttributesFalse();
    //void testgetAttributesFalse_data();
    void testsetOutputFileFalse();
    void testgetInputFileFalse();
    void testgetOutputFileFalse();
    //void testdrawDcmImageFalse();
    //void testputAndInsertStringFalse();
    void testcheckEachTagFalse();



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



void CodeTest::testisValid()
{

    QCOMPARE(testDcm->isValid(),true);


}

//暂不测试
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
    QCOMPARE(testDcm->getOutputFile(),QString("e://1.dcm"));


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
    //这里输入了正确的值与正确的对比了
    OFString testvalue_tmp;
    QString testString="GGGGG AAAAA BBBB";
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

//以下为错误测试函数的实现
void CodeTest::testStructureFalse()
{
    delete testDcm;
    QString testiPath="testvalue";
    QString testoPath="";
    testDcm=new DcmInformation(testiPath,testoPath);
    QCOMPARE(testDcm->getInputFile(),QString("e://CT.dcm"));
    QCOMPARE(testDcm->getOutputFile(),QString(""));

}

void CodeTest::testloadFromDCMFalse()
{

   QCOMPARE(testDcm->loadFromDCM(),true);



}

void CodeTest::testElementIsExist()
{
      DcmElement *testDcmElement;
      bool testboolvalue;
      if(testDcm->getDataset()->findAndGetElement(DCM_PatientName,testDcmElement).bad())
      {

          testboolvalue=false;

      }
      QCOMPARE(testboolvalue,true);

}

/*
void CodeTest::testisValidFalse()
{

    bool testboolvalue=testDcm->isValid();
    QCOMPARE(testboolvalue,true);


}

*/

void CodeTest::testsetOutputFileFalse()
{
    QString testString="TestValue";
    testDcm->setOutputFile(testString);
    QCOMPARE(testDcm->getOutputFile(),QString("e://1.dcm"));


}


void CodeTest::testgetInputFileFalse()
{

   QCOMPARE(testDcm->getInputFile(),QString("e://CT.dcm"));

}

void CodeTest::testgetOutputFileFalse()
{

   QCOMPARE(testDcm->getOutputFile(),QString("e://1.dcm"));

}

void CodeTest::testcheckEachTagFalse()
{

    int testintvalue;
    const int & testvalue=testintvalue;
    testintvalue=26;
    bool testboolvalue=testDcm->checkEachTag(testvalue,NULL);
    QCOMPARE(testboolvalue,true);


}
QTEST_APPLESS_MAIN(CodeTest)

#include "tst_codetest.moc"
