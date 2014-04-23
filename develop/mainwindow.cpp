#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dcm(NULL),
    InputStatu(0)
{
    ui->setupUi(this);
    EditModeChanged(false);

    QObject::connect(ui->actionQuit,SIGNAL(triggered()),SLOT(QuitWindows()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),SLOT(SelectFile()));
    QObject::connect(ui->actionSave_As,SIGNAL(triggered()),SLOT(SaveFile()));
    QObject::connect(ui->actionEdit,SIGNAL(triggered(bool)),SLOT(EditModeChanged(bool)));
    QObject::connect(ui->btn_Reset,SIGNAL(clicked()),SLOT(ResetPatientInfo()));
    QObject::connect(ui->btn_Save,SIGNAL(clicked()),SLOT(SavePatientInfo2File()));

    QObject::connect(ui->Name,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    QObject::connect(ui->ID,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    QObject::connect(ui->Age,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    QObject::connect(ui->StudyData,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    QObject::connect(ui->ContentData,SIGNAL(editingFinished()),SLOT(UpdataErrorInfo()));
    //QMessageBox::about(this,"",QString::number(ReadConfig().size()));
}
Ui::MainWindow * MainWindow::getui()
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

DcmInformation* MainWindow::getDCMObject()
{
    return this->dcm;
}

QVector<Elementinfo> MainWindow::ReadConfig()
{
    QFile xmlfile;
    QDomDocument doc;
    QString errmsg="";
    xmlfile.setFileName("config.xml");
    if(xmlfile.exists())
    {
        if(!xmlfile.open(QFile::ReadOnly) ||
                !doc.setContent(&xmlfile,&errmsg))
        {
            //"Read Config Failed!"
            QMessageBox::warning(this,"File","Error:"+errmsg);
            xmlfile.close();
            return Config;
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
                Config.push_back(ele);
        }
    }
    xmlfile.close();
    return Config;
}

QString MainWindow::SelectFile()
{
        QString OpenFilePath=QFileDialog::getOpenFileName(
                    NULL,
                    QString::fromStdString("Open File"),
                    QDir::currentPath(),
                    "Dcm(*.dcm)");
        if(!OpenFilePath.isEmpty())
        {
            DcmInformation* tmp = dcm;
            dcm = new DcmInformation(OpenFilePath);
            if(LoadFile())
            {
                InitDCMObject(tmp);
            }
            else
            {
                InitDCMObject(dcm);
                dcm = tmp;
                QMessageBox::warning(this,"Warning","Failed to open file");
            }
        }
        return OpenFilePath;
}

bool MainWindow::LoadFile()
{
    bool result = true;
    if(dcm->loadFromDCM())
    {
      QPixmap qmap = dcm->drawDcmImage(ui->DCMPaint->width(),ui->DCMPaint->height());
      PaintDCM(qmap);
      FilePatientInfo = dcm->getAttributes();
      ResetPatientInfo();
    }
    else
    {
       result = false;
    }
    return result;
}

void MainWindow::SaveFile()
{
   if(dcm!=NULL)
   {
     QString spath = QFileDialog::getSaveFileName(
                 NULL,
                 QString::fromStdString("Save File"),
                 QDir::currentPath(),"Dcm(*.dcm) ;; Xml(*.xml)");
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
        ui->StudyData->setReadOnly(false);
        ui->ContentData->setReadOnly(false);
    }
    else
    {
        ui->btn_Reset->setHidden(true);
        ui->btn_Save->setHidden(true);
        ui->Name->setReadOnly(true);
        ui->ID->setReadOnly(true);
        ui->Age->setReadOnly(true);
        ui->StudyData->setReadOnly(true);
        ui->ContentData->setReadOnly(true);
    }
}

void MainWindow::FillPatientInfo(PatientInfo Type, QString ValueFiled)
{
    switch(Type)
    {
    case PatientID:  ui->ID->setText(ValueFiled);break;
    case PatientName:ui->Name->setText(ValueFiled);break;
    case PatientAge: ui->Age->setText(ValueFiled);break;
    case StudyData:ui->StudyData->setText(ValueFiled);break;
    case ContentData:ui->ContentData->setText(ValueFiled);break;
    }
}

void MainWindow::SavePatientInfo2File()
{
    dcm->putAndInsertString(0x0010,0x0010,ui->Name->text());
    dcm->putAndInsertString(0x0010,0x0020,ui->ID->text());
    dcm->putAndInsertString(0x0010,0x1010,ui->Age->text());
    dcm->putAndInsertString(0x0008,0x0020,ui->StudyData->text());
    dcm->putAndInsertString(0x0008,0x0023,ui->ContentData->text());
    dcm->saveFile(dcm->getInputFile().toStdString().c_str());
    LoadFile();
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
    UpdataErrorInfo();
}

void MainWindow::PaintDCM(QPixmap &DCMPix)
{
    ui->DCMPaint->setPixmap(DCMPix);
}

void MainWindow::UpdataErrorInfo()
{
    ui->IDException->setText(
                (true == CheckDataValid(PatientID,ui->ID->text()))?
                    "":"Error");
    ui->NameException->setText(
                (true == CheckDataValid(PatientName,ui->Name->text()))?
                    "":"Error");
    ui->AgeException->setText(
                (true == CheckDataValid(PatientAge,ui->Age->text()))?
                    "":"Error");
    ui->StudyDataException->setText(
                (true == CheckDataValid(StudyData,ui->StudyData->text()))?
                    "":"Error");
    ui->ContentDataException->setText(
                (true == CheckDataValid(ContentData,ui->ContentData->text()))?
                    "":"Error");
    if(InputStatu != 0)
        ui->btn_Save->setEnabled(false);
    else
        ui->btn_Save->setEnabled(true);
}

bool MainWindow::CheckDataValid(PatientInfo VRType,const QString Value)
{
    bool result = true;
    switch(VRType)
    {
    case PatientID:
        result = dcm->checkEachTag(10,Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputStatu,PatientID)):
                    (setflag(InputStatu,PatientID));
        break;
    case PatientName:
        result = dcm->checkEachTag(15,Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputStatu,PatientName)):
                    (setflag(InputStatu,PatientName));
        break;
    case PatientAge:
        result = dcm->checkEachTag(1,Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputStatu,PatientAge)):
                    (setflag(InputStatu,PatientAge));
        break;
    case StudyData:
        result = dcm->checkEachTag(4,Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputStatu,StudyData)):
                    (setflag(InputStatu,StudyData));
        break;
    case ContentData:
        result = dcm->checkEachTag(4,Value.toStdString().c_str());
        (result == true)?
                    (clearflag(InputStatu,ContentData)):
                    (setflag(InputStatu,ContentData));
        break;
    }
    return result;
}

MainWindow::~MainWindow()
{
    delete dcm;
    delete ui;
}
