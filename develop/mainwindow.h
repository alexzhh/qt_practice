#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDecoder>
#include <QAbstractItemModel>
#include "dcminformation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum PatientInfo{PatientID=0,PatientName,PatientAge,StudyData,ContentData};
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString OpenFilePath;
    QVector<DcmElement*> FilePatientInfo;
    QVector<DcmElement*> NewPatientInfo;
    DcmInformation dcm;
public:
    void PaintDCM(QPixmap &DCMPix);
public slots:
    void OpenFile();
    void SaveFile();
    void QuitWindows();
    void EditModeChanged(bool);
    void FillPatientInfo(PatientInfo Type,QString ValueFiled);
    void SavePatientInfo2File();
    void ResetPatientInfo();
    //void CheckDataValid();
};

#endif // MAINWINDOW_H
