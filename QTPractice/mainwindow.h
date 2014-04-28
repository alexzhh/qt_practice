#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QtXml/QDomNodeList>
#include <QFile>
#include <QFileDialog>
#include <QVector>
#include "dcminformation.h"

namespace Ui {
class MainWindow;
}

#define setflag(data,pos) (data=(data | 1<<pos))
#define clearflag(data,pos) (data=(data & ~(1<<pos)))

//A struct Save single Config information
typedef struct Elementinfo
{
    unsigned short GTag;
    unsigned short ETag;
    QString TagName;
    QString VRDescription;
    int     EVR;
}Elementinfo;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum PatientInfo
    {
        PatientID=0,
        PatientName,
        PatientAge,
        StudyData,
        ContentData
    };
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //Save some Patient Information from file
    //patient name,patient age,patient id,study date,content date etc.
    QVector<DcmElement*> FilePatientInfo;
    DcmInformation* dcm;
    //save config information from .xml
    QVector<Elementinfo> Config;
    //all user input flag,0 if ok,nonzero otherwise
    unsigned long InputStatu;
public:
    //get InputStatu
    unsigned long GetInputState();
    //get ui for unit test
    Ui::MainWindow * getui();
    //get dcminformation function for unite test
    DcmInformation* getDCMObject();
    //set dcminformation function for unite test,pass a filepath to it
    DcmInformation* setDCMObject(QString FilePath);
    //Paint DCM image
    void PaintDCM(QPixmap &DCMPix);
    //read config from .xml file
    QVector<Elementinfo> ReadConfig();
    //init dcmobject(free space)
    void InitDCMObject(DcmInformation* dcmObject);
public slots:
    //Choose a file from local disk to open,return Filepath selected
    QString SelectFile();
    //pass Filepath to construct dcm object
    bool LoadFile(QString OpenFilePath);
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
