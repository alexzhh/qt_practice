#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextDecoder>
#include <QFile>
#include <QPixmap>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QString>
#include "dcminformation.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum PatientInfo{PatientID=0,PatientName,PatientAge,PatientStudyTime,PatientImageTime};
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString OpenFilePath;
    QString SaveFilePath;
    QVector<AttrElements> FilePatientInfo;
    QVector<AttrElements> NewPatientInfo;
    DcmInformation dcm;
    DcmDataset data;
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
