#include <QApplication>
#include <QtWidgets>
#include <QtTest/QtTest>
#include "../QTPractice/imageview.h"
#include "../QTPractice/dcminformation.h"
#include "../QTPractice/mainwindow.h"
#include "../QTPractice/ui_mainwindow.h"
class TestGui: public QObject
{
    Q_OBJECT
private:
    MainWindow* m;
    //DcmInformation* dcmInfo;
private slots:
    void testInitial();
    void testALoadFile();
    void testLoadFile();
    void testEditModeChanged();
    void testAEditModeChanged();


    /*
    void testFillPatientInfo();
    void testSavePatientInfo2File();
    void testResetPatientInfo();
    void testPaintDCM();
    void testUpdataErrorInfo();
    void testCheckDataValid();



    void testSelectFile();
    void testASelectFile();

    void testSaveFile();
    void testASaveFile();

    void testAFillPatientInfo();
    void testASavePatientInfo2File();
    void testAResetPatientInfo();
    void testAPaintDCM();
    void testAUpdataErrorInfo();
    void testACheckDataValid();*/


    void cleanupTestCase();
};

//before loading dcm file
void TestGui::testInitial()
{
    m = new MainWindow();
    QVERIFY(m->getDCMObject()==NULL);
    QVERIFY(m->GetInputState()==0);
    QVERIFY(m->ReadConfig().isEmpty());
    QVERIFY(!m->getui()->DCMPaint->pixmap());     // Attention:If no pixmap has been set this will return 0
    QVERIFY(m->getui()->ID->text().isEmpty());
    QVERIFY(m->getui()->Age->text().isEmpty());
    QVERIFY(m->getui()->Name->text().isEmpty());
    QVERIFY(m->getui()->ContentData->text().isEmpty());
    QVERIFY(m->getui()->StudyData->text().isEmpty());
    QVERIFY(m->getui()->btn_Save->isHidden());
    QVERIFY(m->getui()->btn_Save->isHidden());
}
void TestGui::testALoadFile()
{
    QVERIFY(m->LoadFile("../..//..//QTPractice//CodeTest//error.dcm")==false);
}

void TestGui::testLoadFile(){
    QVERIFY(m->LoadFile("../..//..//QTPractice//CodeTest//CT.dcm")==true);
}


//void TestGui::testSaveFile(){

//}

void TestGui::testEditModeChanged(){
    m->EditModeChanged(false),QString("");
    QCOMPARE(m->getui()->Age->isReadOnly(),true);
    QCOMPARE(m->getui()->Name->isReadOnly(),true);
    QCOMPARE(m->getui()->ID->isReadOnly(),true);
    QCOMPARE(m->getui()->ContentData->isReadOnly(),true);
    QCOMPARE(m->getui()->StudyData->isReadOnly(),true);
    QCOMPARE(m->getui()->btn_Save->isHidden(),true);
    QCOMPARE(m->getui()->btn_Reset->isHidden(),true);
}

void TestGui::testAEditModeChanged(){
    m->EditModeChanged(true);

    QCOMPARE(m->getui()->Age->isReadOnly(),false);
    QCOMPARE(m->getui()->Name->isReadOnly(),false);
    QCOMPARE(m->getui()->ID->isReadOnly(),false);
    QCOMPARE(m->getui()->ContentData->isReadOnly(),false);
    QCOMPARE(m->getui()->StudyData->isReadOnly(),false);
    QCOMPARE(m->getui()->btn_Save->isHidden(),false);
    QCOMPARE(m->getui()->btn_Reset->isHidden(),false);
}
//void TestGui::testFillPatientInfo(){
//}
//void TestGui::testSavePatientInfo2File(){
//}
//void TestGui::testResetPatientInfo(){
//}
//void TestGui::testPaintDCM(){
//    QVERIFY(m->getui()->DCMPaint->pixmap()!=0);

//}
//void TestGui::testUpdataErrorInfo(){
//}
//void TestGui::testCheckDataValid(){
//}


//void TestGui::testASelectFile(){
//    m->setDCMObject(new DcmInformation("CT.dcm"));
//}

//savefile has been test in the dcminfomation class
/*void TestGui::testASaveFile(){

}

void TestGui::testAFillPatientInfo(){
    m->FillPatientInfo(MainWindow::PatientAge,"060Y");
    QCOMPARE(m->getui()->Age->text(),"060Y");
    m->FillPatientInfo(MainWindow::PatientID,"000484");
    QCOMPARE(m->getui()->ID->text(),"000484");
    m->FillPatientInfo(MainWindow::PatientName,"test");
    QCOMPARE(m->getui()->Name->text(),"test");
    m->FillPatientInfo(MainWindow::ContentData,"20090207");
    QCOMPARE(m->getui()->ContentData->text(),"20090207");
    m->FillPatientInfo(MainWindow::StudyData,"20090207");
    QCOMPARE(m->getui()->StudyData->text(),"20090207");

}
void TestGui::testASavePatientInfo2File(){
    QTest::keyClicks(m->getui()->Age, "160Y");
    QTest::keyClicks(m->getui()->ID, "100484");
    QTest::keyClicks(m->getui()->Name, "1est");
    QTest::keyClicks(m->getui()->ContentData, "10090207");
    QTest::keyClicks(m->getui()->StudyData, "10090207");
    m->SavePatientInfo2File();
    QCOMPARE(m->getui()->Age->text(),"160Y");
    QCOMPARE(m->getui()->ID->text(),"100484");
    QCOMPARE(m->getui()->Name->text(),"1est");
    QCOMPARE(m->getui()->ContentData->text(),"10090207");
    QCOMPARE(m->getui()->StudyData->text(),"10090207");
    //reset
    QTest::keyClicks(m->getui()->Age, "060Y");
    QTest::keyClicks(m->getui()->ID, "000484");
    QTest::keyClicks(m->getui()->Name, "test");
    QTest::keyClicks(m->getui()->ContentData, "20090207");
    QTest::keyClicks(m->getui()->StudyData, "20090207");
    m->SavePatientInfo2File();
}
void TestGui::testAResetPatientInfo(){
    QTest::keyClicks(m->getui()->Age, "160Y");
    QTest::keyClicks(m->getui()->ID, "100484");
    QTest::keyClicks(m->getui()->Name, "1est");
    QTest::keyClicks(m->getui()->ContentData, "10090207");
    QTest::keyClicks(m->getui()->StudyData, "10090207");
    m->ResetPatientInfo();
    QCOMPARE(m->getui()->Age->text(),"060Y");
    QCOMPARE(m->getui()->ID->text(),"000484");
    QCOMPARE(m->getui()->Name->text(),"test");
    QCOMPARE(m->getui()->ContentData->text(),"20090207");
    QCOMPARE(m->getui()->StudyData->text(),"20090207");
}
void TestGui::testAPaintDCM(){

}
void TestGui::testAUpdataErrorInfo(){
    //ID和Name都没有效验，所以没测
    //error testing
    QTest::keyClicks(m->getui()->Age, "0600");
    QTest::keyClicks(m->getui()->ContentData, "test");
    QTest::keyClicks(m->getui()->StudyData, "test");
    m->UpdataErrorInfo();
    QCOMPARE(m->getui()->AgeException->text(),"Error");
    QCOMPARE(m->getui()->ContentDataException->text(),"Error");
    QCOMPARE(m->getui()->StudyDataException->text(),"Error");
    //correct testing
    QTest::keyClicks(m->getui()->Age, "060Y");
    QTest::keyClicks(m->getui()->ID, "000484");
    QTest::keyClicks(m->getui()->Name, "test");
    QTest::keyClicks(m->getui()->ContentData, "20090207");
    QTest::keyClicks(m->getui()->StudyData, "20090207");
    m->UpdataErrorInfo();
    QCOMPARE(m->getui()->AgeException->text(),"");
    QCOMPARE(m->getui()->ContentDataException->text(),"");
    QCOMPARE(m->getui()->StudyDataException->text(),"");
    QCOMPARE(m->getui()->IDException->text(),"");
    QCOMPARE(m->getui()->NameException->text(),"");

}
void TestGui::testACheckDataValid(){


}*/

void TestGui::cleanupTestCase()
{
    if(m!=NULL)
    {
        delete m;
        m=NULL;
    }
}

QTEST_MAIN(TestGui)
#include "tst_uitest_2test.moc"
