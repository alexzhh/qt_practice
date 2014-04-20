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
    //all user input flag,0 if ok,nonzero otherwise
    unsigned long InputStatu;
public:
    //Paint DCM image
    void PaintDCM(QPixmap &DCMPix);
public slots:
    //Choose a file from local disk to open,return Filepath selected
    QString SelectFile();
    //init dcmobject(free space)
    void InitDCMObject(DcmInformation* dcmObject);
    //pass Filepath to construct dcm object
    bool LoadFile();
    //interface ,Save as another file format
    void SaveFile();
    //Exit Windows
    void QuitWindows();
    //when Edit menu checked,user can rewrite patient info,
    //otherwise,it would be read only
    void EditModeChanged(bool);
    //display Patient informatin
    void FillPatientInfo(PatientInfo Type,QString ValueFiled);
    //Write Patient Information(modified by user) to File
    void SavePatientInfo2File();
    //Use default Patient information
    void ResetPatientInfo();
    //Alert while error input
    void UpdataErrorInfo();
    //validate user input,true if ok, false otherwise
    bool CheckDataValid(PatientInfo VRType,const QString Value);
};
#endif // MAINWINDOW_H
