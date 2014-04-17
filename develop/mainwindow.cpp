#include "mainwindow.h"
#include "ui_mainwindow.h"

using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionQuit,SIGNAL(triggered()),SLOT(QuitWindows()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),SLOT(OpenFile()));
    QObject::connect(ui->actionSave_As,SIGNAL(triggered()),SLOT(SaveFile()));
    QObject::connect(ui->actionEdit,SIGNAL(triggered(bool)),this,SLOT(EditModeChanged(bool)));
    QObject::connect(ui->btn_Reset,SIGNAL(clicked()),SLOT(ResetPatientInfo()));
    QObject::connect(ui->btn_Save,SIGNAL(clicked()),SLOT(SavePatientInfo2File()));
    emit EditModeChanged(false);
    dcm = NULL;
    //QMessageBox::about(NULL,"",QString::number(ui->tableWidget->rowCount())+QString::number(ui->tableWidget->columnCount()));

}

void MainWindow::OpenFile()
{

    if(dcm==NULL) {
        QString OpenFilePath=QFileDialog::getOpenFileName(
                    NULL,
                    QString::fromStdString("Open File"),
                    QDir::currentPath(),
                    "Dcm(*.dcm)");
         dcm = new DcmInformation(OpenFilePath);
    }

    if(dcm->loadFromDCM())
    {
      QPixmap qmap = dcm->drawDcmImage(ui->DCMPaint->width(),ui->DCMPaint->height());
      PaintDCM(qmap);
      FilePatientInfo = dcm->getAttributes();
      NewPatientInfo = FilePatientInfo;
      ResetPatientInfo();
    }
}

void MainWindow::SaveFile()
{
   if(dcm!=NULL)
   {
     QString spath = QFileDialog::getSaveFileName(
                 NULL,
                 QString::fromStdString("Save File"),
                 QDir::currentPath());
     dcm->setOutputFile(spath);
     dcm->customSaveFile();
   }
   else
    QMessageBox::warning(
                this,"DCM",
                "Source file not found,please open file first");
}

void MainWindow::QuitWindows()
{
    if(QMessageBox::warning(this,QString::fromStdString("Warning"),
                            QString::fromStdString("Quit Windows?"),
                            QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit close();
    }
}

void MainWindow::EditModeChanged(bool EditChecked)
{

    if(EditChecked)   //Edit Checked
    {
        if(dcm==NULL)
        {
            QMessageBox::warning(this,"Error","No File Opened!");
            ui->actionEdit->setChecked(false);
            return ;
        }
        ui->btn_Reset->setHidden(false);
        ui->btn_Save->setHidden(false);
        ui->Name->setReadOnly(false);
        ui->ID->setReadOnly(false);
        ui->Age->setReadOnly(false);
    }
    else
    {
        ui->btn_Reset->setHidden(true);
        ui->btn_Save->setHidden(true);
        ui->Name->setReadOnly(true);
        ui->ID->setReadOnly(true);
        ui->Age->setReadOnly(true);
        ui->ImageTime->setReadOnly(true);
        ui->StudyTime->setReadOnly(true);
    }
}

void MainWindow::FillPatientInfo(PatientInfo Type, QString ValueFiled)
{
    switch(Type)
    {
    case PatientID:  ui->ID->setText(ValueFiled);break;
    case PatientName:ui->Name->setText(ValueFiled);break;
    case PatientAge: ui->Age->setText(ValueFiled);break;
    case StudyData:ui->StudyTime->setText(ValueFiled);break;
    case ContentData:ui->ImageTime->setText(ValueFiled);break;
    }
}

void MainWindow::SavePatientInfo2File()
{
    DcmDataset* Data=dcm->getDataset();
    Data->putAndInsertString(DCM_PatientName,ui->Name->text().toStdString().c_str());
    Data->putAndInsertString(DCM_PatientID,ui->ID->text().toStdString().c_str());
    Data->putAndInsertString(DCM_PatientAge,ui->Age->text().toStdString().c_str());
    Data->putAndInsertString(DCM_StudyDate,ui->StudyTime->text().toStdString().c_str());
    Data->putAndInsertString(DCM_ContentDate,ui->ImageTime->text().toStdString().c_str());
    dcm->saveFile(dcm->getInuptFile().toStdString().c_str());
    OpenFile();
}

void MainWindow::ResetPatientInfo()
{
    int index=0;
    foreach(DcmElement* dc,FilePatientInfo)
    {
        if(dc!=NULL)
        {
            OFString ValueFiled="";
            dc->getOFString(ValueFiled,0);
            FillPatientInfo(PatientInfo(index),ValueFiled.c_str());
        }
        else
        {
            FillPatientInfo(PatientInfo(index),"");
        }
            index++;
    }
}

void MainWindow::PaintDCM(QPixmap &DCMPix)
{
    ui->DCMPaint->setPixmap(DCMPix);
}

void MainWindow::CheckDataValid()
{

}

MainWindow::~MainWindow()
{
    delete dcm;
    delete ui;
}
