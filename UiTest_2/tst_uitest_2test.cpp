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
private slots:
    void testConstruct();
    void cleanupTestCase();
};


void TestGui::testConstruct()
{
    m = new MainWindow();
    QVERIFY(m->getDCMObject()==NULL);
    QVERIFY(m->GetInputState()==0);
    QVERIFY(m->ReadConfig().isEmpty());
//   QVERIFY(m->getui()->DCMPaint->pixmap()->isNull());
//    QVERIFY(m->getui()->ID->text().isEmpty());
//    QVERIFY(m->getui()->Age->text().isEmpty());
//    QVERIFY(m->getui()->Name->text().isEmpty());
//    QVERIFY(m->getui()->ContentData->text().isEmpty());
//    QVERIFY(m->getui()->StudyData->text().isEmpty());
//    QVERIFY(m->getui()->btn_Save->isHidden());
//    QVERIFY(m->getui()->btn_Save->isHidden());
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
