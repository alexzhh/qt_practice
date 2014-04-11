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
    emit EditModeChanged(false);
    //QMessageBox::about(NULL,"",QString::number(ui->tableWidget->rowCount())+QString::number(ui->tableWidget->columnCount()));

}

void MainWindow::OpenFile()
{
//   DcmElement *dcmelement = NULL;
   OpenFilePath = dcm.OpenFile("DCM File(*.dcm)");
   if(dcm.initial(OpenFilePath))
    {
      PaintDCM(dcm.drawDcmImage(ui->DCMPaint->width(),ui->DCMPaint->height()));
      FilePatientInfo = dcm.getAttributes();
//      for(int i=0;i<FilePatientInfo.length();++i)
//      {
//        dcmelement = FilePatientInfo.at(i);
//        if(dcmelement != NULL)
//        {
//          DcmTag tag = dcmelement->getTag();
//          QMessageBox::about(
//                  this,"DCM",QString(tag.toString().c_str()));
//        }
//      }
//      NewPatientInfo = FilePatientInfo;
//      ResetPatientInfo();
    }
}

void MainWindow::SaveFile()
{
   if(!OpenFilePath.isEmpty())
   {
     QString spath = dcm.SaveFile("DCM File(*.dcm);;XML File(*.xml)");
     dcm.dcm2Xml(spath,OpenFilePath);
   }
   else
    QMessageBox::about(
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
    if(EditChecked)   //Edit选中时
    {
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
//    switch(Type)
//    {
//    case PatientID:  ui->ID->setText(ValueFiled);break;
//    case PatientName:ui->Name->setText(ValueFiled);break;
//    case PatientAge: ui->Age->setText(ValueFiled);break;
//    case PatientStudyTime:ui->StudyTime->setText(ValueFiled);break;
//    case PatientImageTime:ui->ImageTime->setText(ValueFiled);break;
//    }
}

void MainWindow::SavePatientInfo2File()
{
//    if(FilePatientInfo != NewPatientInfo)
//    {
//        //Do Write File
//    }
}

void MainWindow::ResetPatientInfo()
{
//    foreach(AttrElements element,NewPatientInfo)
//    {
//        FillPatientInfo(PatientInfo(element.type),element.value);
//    }
}

void MainWindow::PaintDCM(QPixmap &DCMPix)
{
    ui->DCMPaint->setPixmap(DCMPix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
