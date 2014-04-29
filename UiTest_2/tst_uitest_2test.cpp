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
    void testSaveFile();
    void testEditModeChanged();
    void testAEditModeChanged();
    void testAFillPatientInfo();
    void testPaintDCM();
    //void testASavePatientInfo2File_data();
    void testASavePatientInfo2File();

    void testAResetPatientInfo();
    void testUpdataErrorInfo();
    void testAUpdataErrorInfo();
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
    QVERIFY(m->LoadFile("../../qt_practice/CodeTest/error.dcm")==false);
}

void TestGui::testLoadFile(){
    QVERIFY(m->LoadFile("../../qt_practice/CodeTest/CT.dcm")==true);
}


void TestGui::testSaveFile(){
    m->getDCMObject()->setOutputFile("test.dcm");
    m->getDCMObject()->customSaveFile();
    QVERIFY(m->LoadFile("test.dcm")==true);
    m->getDCMObject()->setOutputFile("test.xml");
    m->getDCMObject()->customSaveFile();
    QVERIFY(QFile("test.xml").exists());
    QFile("test.xml").remove();
    QFile("test.dcm").remove();
}


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


void TestGui::testAFillPatientInfo(){
    m->FillPatientInfo(MainWindow::PatientAge,"060Y");
    QVERIFY(m->getui()->Age->text()=="060Y");
    m->FillPatientInfo(MainWindow::PatientID,"000484");
    QVERIFY(m->getui()->ID->text()=="000484");
    m->FillPatientInfo(MainWindow::PatientName,"test");
    QVERIFY(m->getui()->Name->text()=="test");
    m->FillPatientInfo(MainWindow::ContentData,"20090207");
    QVERIFY(m->getui()->ContentData->text()=="20090207");
    m->FillPatientInfo(MainWindow::StudyData,"20090207");
    QVERIFY(m->getui()->StudyData->text()=="20090207");


}
void TestGui::testPaintDCM(){
    QVERIFY(m->getui()->DCMPaint->pixmap()!=0);

}
/*
void TestGui::testASavePatientInfo2File_data(){
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");
    QTestEventList listAge;
    listAge.addKeyClick(Qt::Key_Backspace,Qt::ControlModifier);
    listAge.addKeyClicks("160Y");
    QTest::newRow("age") << listAge << "160Y";
    QTestEventList listID;
    listID.addKeyClick(Qt::Key_Backspace,Qt::ControlModifier);
    listID.addKeyClicks("100484");
    QTest::newRow("ID") << listID << "100484";
    QTestEventList listName;
    listName.addKeyClick(Qt::Key_Backspace,Qt::ControlModifier);
    listName.addKeyClicks("test");
    QTest::newRow("Name") << listName << "test";
    QTestEventList listContentData;
    listContentData.addKeyClick(Qt::Key_Backspace,Qt::ControlModifier);
    listContentData.addKeyClicks("10090207");
    QTest::newRow("ContentData") << listContentData << "10090207";
    QTestEventList listStudyData;
    listStudyData.addKeyClick(Qt::Key_Backspace,Qt::ControlModifier);
    listStudyData.addKeyClicks("10090207");
    QTest::newRow("StudyData") << listStudyData << "10090207";
}
*/

void TestGui::testASavePatientInfo2File(){
    m->EditModeChanged(true);
    QTest::keyClick(m->getui()->Age, Qt::Key_Backspace,Qt::ControlModifier);
    QTest::keyClicks(m->getui()->Age, "160Y");
    QTest::keyClick(m->getui()->ID, Qt::Key_Backspace,Qt::ControlModifier);
    QTest::keyClicks(m->getui()->ID, "100484");
    QTest::keyClick(m->getui()->Name, Qt::Key_Backspace,Qt::ControlModifier);
    QTest::keyClicks(m->getui()->Name, "1est");
    QTest::keyClick(m->getui()->ContentData, Qt::Key_Backspace,Qt::ControlModifier);
    QTest::keyClicks(m->getui()->ContentData, "10090207");
    QTest::keyClick(m->getui()->StudyData, Qt::Key_Backspace,Qt::ControlModifier);
    QTest::keyClicks(m->getui()->StudyData, "10090207");
    m->SavePatientInfo2File();
    QVERIFY(m->getui()->Age->text()=="160Y");
    QVERIFY(m->getui()->ID->text()=="100484");
    QVERIFY(m->getui()->Name->text()=="1est");
    QVERIFY(m->getui()->ContentData->text()=="10090207");
    QVERIFY(m->getui()->StudyData->text()=="10090207");
    //reset
    QTest::keyClick(m->getui()->Age, Qt::Key_Backspace,Qt::ControlModifier);
    QTest::keyClicks(m->getui()->Age, "060Y");
    QTest::keyClick(m->getui()->ID, Qt::Key_Backspace,Qt::ControlModifier);
    QTest::keyClicks(m->getui()->ID, "000484");
    QTest::keyClick(m->getui()->Name, Qt::Key_Backspace,Qt::ControlModifier);
    QTest::keyClicks(m->getui()->Name, "test");
    QTest::keyClick(m->getui()->ContentData, Qt::Key_Backspace,Qt::ControlModifier);
    QTest::keyClicks(m->getui()->ContentData, "20090207");
    QTest::keyClick(m->getui()->StudyData, Qt::Key_Backspace,Qt::ControlModifier);
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
    QVERIFY(m->getui()->Age->text()=="060Y");
    QVERIFY(m->getui()->ID->text()=="000484");
    QVERIFY(m->getui()->Name->text()=="test");
    QVERIFY(m->getui()->ContentData->text()=="20090207");
    QVERIFY(m->getui()->StudyData->text()=="20090207");
}
void TestGui::testUpdataErrorInfo(){
    //correct testing
    m->UpdataErrorInfo();
    QVERIFY(m->getui()->AgeException->text()=="");
    QVERIFY(m->getui()->ContentDataException->text()=="");
    QVERIFY(m->getui()->StudyDataException->text()=="");
    QVERIFY(m->getui()->IDException->text()=="");
    QVERIFY(m->getui()->NameException->text()=="");
}

void TestGui::testAUpdataErrorInfo(){
    //ID和Name都没有效验，所以没测
    //error testing
    QTest::keyClicks(m->getui()->Age, "0600");
    QTest::keyClicks(m->getui()->ContentData, "test");
    QTest::keyClicks(m->getui()->StudyData, "test");
    m->UpdataErrorInfo();
    QVERIFY(m->getui()->AgeException->text()=="Error");
    QVERIFY(m->getui()->ContentDataException->text()=="Error");
    QVERIFY(m->getui()->StudyDataException->text()=="Error");
}

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
