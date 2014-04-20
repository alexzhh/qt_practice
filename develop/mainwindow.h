#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDecoder>
#include <QAbstractItemModel>
#include "dcminformation.h"
#include <QFileDialog>
namespace Ui {
class MainWindow;
}

#define setflag(data,pos) (data=(data | 1<<pos))
#define clearflag(data,pos) (data=(data & ~(1<<pos)))

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum PatientInfo{PatientID=0,PatientName,PatientAge,StudyData,ContentData};
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<DcmElement*> FilePatientInfo;
    DcmInformation* dcm;
    unsigned long InputStatu;
public:
    void PaintDCM(QPixmap &DCMPix);
public slots:
    QString SelectFile();
    void InitDCMObject(DcmInformation* dcmObject);
    bool LoadFile();
    void SaveFile();
    void QuitWindows();
    void EditModeChanged(bool);
    void FillPatientInfo(PatientInfo Type,QString ValueFiled);
    void SavePatientInfo2File();
    void ResetPatientInfo();
    void UpdataErrorInfo();
    bool CheckDataValid(PatientInfo VRType,const QString Value);
};
#endif // MAINWINDOW_H
