#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    dcm(NULL),
    ui(new Ui::MainWindow),
    inputState(0)
{
    ui->setupUi(this);
    EditModeChanged(false);

    QObject::connect(ui->actionQuit,SIGNAL(triggered()),SLOT(QuitWindows()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),SLOT(SelectOpenFile()));
    QObject::connect(ui->actionSave_As,SIGNAL(triggered()),SLOT(SelectSaveFile()));
    QObject::connect(ui->actionEdit,SIGNAL(triggered(bool)),SLOT(EditModeChanged(bool)));
    QObject::connect(ui->btn_Reset,SIGNAL(clicked()),SLOT(ResetPatientInfo()));
    QObject::connect(ui->btn_Save,SIGNAL(clicked()),SLOT(SavePatientInfo2File()));

    QObject::connect(ui->Name,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    QObject::connect(ui->ID,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    QObject::connect(ui->Age,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    QObject::connect(ui->StudyDate,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    QObject::connect(ui->ContentDate,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    //QMessageBox::about(this,"",QString::number(ReadConfig().size()));

}

unsigned long MainWindow::GetInputState()
{
    return this->inputState;
}

Ui::MainWindow * MainWindow::GetUi()
{
    return this->ui;
}

void MainWindow::InitDCMObject(DcmInformation* dcmObject)
{
    if(dcmObject!=NULL)
    {
        delete dcmObject;
        dcmObject = NULL;
    }
}

void MainWindow::PopMessage(int msec, QString title, QString text, QWidget *parent)
{
    QMessageBox* m =new QMessageBox(QMessageBox::NoIcon,title,text,QMessageBox::Close,parent);
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();
    QTimer::singleShot(msec,m,SLOT(close()));
}

DcmInformation* MainWindow::GetDCMObject()
{
    return this->dcm;
}

QVector<Elementinfo> MainWindow::ReadConfig(QString configPath)
{
    QFile xmlfile;
    QDomDocument doc;
    QString errmsg="";
    xmlfile.setFileName(configPath);
    if(xmlfile.exists())
    {
        if(!xmlfile.open(QFile::ReadOnly) ||
                !doc.setContent(&xmlfile,&errmsg))
        {
            //"Read Config Failed!"
            QMessageBox::warning(this,"File","Error:"+errmsg);
            xmlfile.close();
            return config;
        }
        QDomNodeList nodelist=doc.elementsByTagName("Element");
        for(int i=0;i<nodelist.size();i++)
        {
            Elementinfo ele;
            ele.EVR = nodelist.at(i).toElement().text().toInt();
            QDomNamedNodeMap attrib=nodelist.at(i).attributes();
            bool ValidConfigItem=true;
            for(int j=0;j<attrib.size();j++)
            {
                bool ok=true;
                if("GTag"==attrib.item(j).nodeName())
                {
                    QString value=attrib.item(j).nodeValue();
                    ele.GTag=value.toUShort(&ok,16);
                    if(!value.toLower().startsWith("0x") ||
                            !(value.length()==6) ||
                            !ok)
                    {
                        ValidConfigItem=false;
                        break;
                    }
                }
                else if("ETag"==attrib.item(j).nodeName())
                {
                    QString value=attrib.item(j).nodeValue();
                    ele.ETag=attrib.item(j).nodeValue().toUShort(&ok,16);
                    if(!value.toLower().startsWith("0x") ||
                            !(value.length()==6) ||
                            !ok)
                    {
                        ValidConfigItem=false;
                        break;
                    }
                }
                else if("TagName"==attrib.item(j).nodeName())
                    ele.TagName=attrib.item(j).nodeValue();
                else if("VRDescription"==attrib.item(j).nodeName())
                    ele.VRDescription=attrib.item(j).nodeValue();
            }
            if(ValidConfigItem)
                config.push_back(ele);
        }
    }
    xmlfile.close();
    return config;
}

QString MainWindow::SelectOpenFile()
{
        QString OpenFilePath=QFileDialog::getOpenFileName(
                    NULL,
                    QString::fromStdString("Open File"),
                    QDir::currentPath(),
                    "DCM File(*.dcm)"
                    );
        if(!OpenFilePath.isEmpty())
        {
            LoadFile(OpenFilePath);
        }
        return OpenFilePath;
}

bool MainWindow::LoadFile(QString openFilePath)
{
    bool result = true;
    DcmInformation* tmp = dcm;
    dcm = new DcmInformation(openFilePath);
    if(dcm->loadFromDCM())
    {
        InitDCMObject(tmp);
        QPixmap qmap = dcm->drawDcmImage(ui->DCMPaint->width(),ui->DCMPaint->height());
        Paint(qmap);
        filePatientInfo = dcm->getAttributes();
        ResetPatientInfo();
    }
    else
    {
        result = false;
        InitDCMObject(dcm);
        dcm = tmp;
        //QMessageBox::warning(this,"Warning","Failed to open file");
        PopMessage(2*1000,"Warning","Failed to open file");
    }
    return result;
}

void MainWindow::SelectSaveFile()
{
   if(dcm!=NULL)
   {
     QString spath = QFileDialog::getSaveFileName(
                 NULL,
                 QString::fromStdString("Save File"),
                 QDir::currentPath(),"Dcm(*.dcm) ;; Xml(*.xml)");
     SaveFile(spath);
   }
   else
   {
       PopMessage(2*1000,"DCM","Source file not found,please open file first",this);
   }
}

void MainWindow::SaveFile(QString filePath)
{
    dcm->setOutputFile(filePath);
    dcm->customSaveFile();
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
            //QMessageBox::warning(this,"Error","No File Opened!");
            PopMessage(2*1000,"Error","No File Opened!",this);
            ui->actionEdit->setChecked(false);
            return ;
        }
        ui->btn_Reset->setHidden(false);
        ui->btn_Save->setHidden(false);
        ui->Name->setReadOnly(false);
        ui->ID->setReadOnly(false);
        ui->Age->setReadOnly(false);
        ui->StudyDate->setReadOnly(false);
        ui->ContentDate->setReadOnly(false);
    }
    else
    {
        ui->btn_Reset->setHidden(true);
        ui->btn_Save->setHidden(true);
        ui->Name->setReadOnly(true);
        ui->ID->setReadOnly(true);
        ui->Age->setReadOnly(true);
        ui->StudyDate->setReadOnly(true);
        ui->ContentDate->setReadOnly(true);
    }
}

void MainWindow::FillPatientInfo(PatientInfo type, QString valueFiled)
{
    switch(type)
    {
    case PatientID:  ui->ID->setText(valueFiled);break;
    case PatientName:ui->Name->setText(valueFiled);break;
    case PatientAge: ui->Age->setText(valueFiled);break;
    case StudyDate:ui->StudyDate->setText(valueFiled);break;
    case ContentDate:ui->ContentDate->setText(valueFiled);break;
    }
}

void MainWindow::SavePatientInfo2File()
{
    dcm->putAndInsertString("PatientName",ui->Name->text());
    dcm->putAndInsertString("PatientID",ui->ID->text());
    dcm->putAndInsertString("PatientAge",ui->Age->text());
    dcm->putAndInsertString("StudyDate",ui->StudyDate->text());
    dcm->putAndInsertString("ContentDate",ui->ContentDate->text());
    dcm->saveFile(dcm->getInputFile().toStdString().c_str());
    LoadFile(dcm->getInputFile());
}

void MainWindow::ResetPatientInfo()
{
    int index=0;
    foreach(DcmElement* dc,filePatientInfo)
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
    UpdataErrorInfo();
}

void MainWindow::Paint(QPixmap &dcmPix)
{
    ui->DCMPaint->setPixmap(dcmPix);

}

void MainWindow::UpdataErrorInfo()
{
    ui->IDException->setText(
                (true == dcm->checkEachTag("PatientID",ui->ID->text().toStdString().c_str()))?
                    "":"Error");
    ui->NameException->setText(
                (true == dcm->checkEachTag("PatientName",ui->Name->text().toStdString().c_str()))?
                    "":"Error");
    ui->AgeException->setText(
                (true == dcm->checkEachTag("PatientAge",ui->Age->text().toStdString().c_str()))?
                    "":"Error");
    ui->StudyDateException->setText(
                (true == dcm->checkEachTag("StudyDate",ui->StudyDate->text().toStdString().c_str()))?
                    "":"Error");
    ui->ContentDateException->setText(
                (true == dcm->checkEachTag("ContentDate",ui->ContentDate->text().toStdString().c_str()))?
                    "":"Error");
    if(inputState != 0)
        ui->btn_Save->setEnabled(false);
    else
        ui->btn_Save->setEnabled(true);
}

bool MainWindow::CheckDataValid(QString patientInfo, const QString value)
{
    bool result = true;
    /*switch(VRType)
    {
    case PatientID:
        result = dcm->checkEachTag("PatientID",Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputState,PatientID)):
                    (setflag(InputState,PatientID));
        break;
    case PatientName:
        result = dcm->checkEachTag("PatientName",Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputState,PatientName)):
                    (setflag(InputState,PatientName));
        break;
    case PatientAge:
        result = dcm->checkEachTag("PatientAge",Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputState,PatientAge)):
                    (setflag(InputState,PatientAge));
        break;
    case StudyDate:
        result = dcm->checkEachTag("StudyDate",Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputState,StudyDate)):
                    (setflag(InputState,StudyDate));
        break;
    case ContentDate:
        result = dcm->checkEachTag("ContentDate",Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputState,ContentDate)):
                    (setflag(InputState,ContentDate));
        break;
    }*/
    return result;
}

MainWindow::~MainWindow()
{
    if(dcm!=NULL)
        delete dcm;

    delete ui;
}
