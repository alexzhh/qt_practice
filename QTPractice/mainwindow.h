#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QtXml/QDomNodeList>
#include <QFile>
#include <QFileDialog>
#include <QVector>
#include <QTimer>
#include "dcminformation.h"

namespace Ui {
class MainWindow;
}

#define setflag(data,pos) (data=(data | 1<<pos))
#define clearflag(data,pos) (data=(data & ~(1<<pos)))

//A struct Save single Config information
//typedef struct Elementinfo
//{
//    unsigned short GTag;
//    unsigned short ETag;
//    QString TagName;
//    QString VRDescription;
//    int     EVR;
//}Elementinfo;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum PatientInfo
    {
        PatientID=0,
        PatientName,
        PatientAge,
        StudyDate,
        ContentDate
    };
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //Save some Patient Information from file
    //patient name,patient age,patient id,study date,content date etc.
    QVector<DcmElement*> filePatientInfo;
    DcmInformation* dcm;
    //save config information from .xml
    QVector<Elementinfo> config;
    //all user input flag,0 if ok,nonzero otherwise
    unsigned long inputState;
public:
    //get InputState
    unsigned long GetInputState();
    //get ui for unit test
    Ui::MainWindow * GetUi();
    //get dcminformation function for unite test
    DcmInformation* GetDCMObject();
    //set dcminformation function for unite test,pass a filepath to it
    DcmInformation* SetDCMObject(QString FilePath);
    //Paint DCM image
    void Paint(QPixmap &dcmPix);
    //read config from .xml file
    QVector<Elementinfo> ReadConfig(QString ConfigPath);
    //init dcmobject(free space)
    void InitDCMObject(DcmInformation* dcmObject);
    //pop up  message
    void PopMessage(int msec,QString title,QString text,QWidget* parent=0);
public slots:
    //Choose a file from local disk to open,return Filepath selected
    QString SelectOpenFile();
    //pass Filepath to construct dcm object
    bool LoadFile(QString openFilePath);
    //select a filepath to save object
    void SelectSaveFile();
    //Save Object to file
    void SaveFile(QString filePath);
    //Exit Windows
    void QuitWindows();
    //when Edit menu checked,user can rewrite patient info,
    //otherwise,it would be read only
    void EditModeChanged(bool);
    //display Patient informatin
    void FillPatientInfo(PatientInfo type,QString valueFiled);
    //Write Patient Information(modified by user) to File
    void SavePatientInfo2File();
    //Use default Patient information
    void ResetPatientInfo();
    //Alert while error input
    void UpdateErrorInfo();
    //validate user input,true if ok, false otherwise
    bool CheckDataValid(QString patientInfo, const QString value);
};
#endif // MAINWINDOW_H
