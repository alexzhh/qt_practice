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

    QObject::connect(ui->Name,SIGNAL(editingFinished()),SLOT(UpdateErrorInfo()));
    QObject::connect(ui->ID,SIGNAL(editingFinished()),SLOT(UpdateErrorInfo()));
    QObject::connect(ui->Age,SIGNAL(editingFinished()),SLOT(UpdateErrorInfo()));
    QObject::connect(ui->StudyDate,SIGNAL(editingFinished()),SLOT(UpdateErrorInfo()));
    QObject::connect(ui->ContentDate,SIGNAL(editingFinished()),SLOT(UpdateErrorInfo()));
    //QMessageBox::about(this,"",QString::number(ReadConfig().size()));
    ReadConfig("");

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

QList<ElementInfo> MainWindow::ReadConfig(QString configPath)
{
  filePatientInfo.push_back(ElementInfo(0x0010,0x0020,"PatientID",""));
  filePatientInfo.push_back(ElementInfo(0x0010,0x0010,"PatientName",""));
  filePatientInfo.push_back(ElementInfo(0x0010,0x1010,"PatientAge",""));
  filePatientInfo.push_back(ElementInfo(0x0008,0x0020,"StudyDate",""));
  filePatientInfo.push_back(ElementInfo(0x0008,0x0023,"ContentDate",""));
  return filePatientInfo;
    /*QFile xmlfile;
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
            ElementInfo ele;
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
    return config;*/
}

QString MainWindow::SelectOpenFile()
{
        QString OpenFilePath=QFileDialog::getOpenFileName(
                    this,
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
        QList<ElementInfo> tmplist;
        foreach(ElementInfo ele,filePatientInfo)
        {
            ele.TagValue = dcm->getDcmQStringValue(ele.GTag,ele.ETag);
            tmplist.push_back(ele);
        }
        filePatientInfo.clear();
        filePatientInfo = tmplist;
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
                 this,
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
    case StudyDate:  ui->StudyDate->setText(valueFiled);break;
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
  foreach(ElementInfo ele,filePatientInfo)
    {
      if(ele.TagName=="PatientName")
        ui->Name->setText(ele.TagValue);
      else if(ele.TagName=="PatientAge")
        ui->Age->setText(ele.TagValue);
      else if(ele.TagName=="PatientID")
        ui->ID->setText(ele.TagValue);
      else if(ele.TagName=="StudyDate")
        ui->StudyDate->setText(ele.TagValue);
      else if(ele.TagName=="ContentDate")
        ui->ContentDate->setText(ele.TagValue);
    }
    UpdateErrorInfo();
}

void MainWindow::Paint(QPixmap &dcmPix)
{
    ui->DCMPaint->setPixmap(dcmPix);
}

void MainWindow::UpdateErrorInfo()
{
    if(dcm!=NULL)
    {
    ui->IDException->setText(
                (true == dcm->checkEachTag("PatientID",ui->ID->text().toStdString().c_str()))?
                    (clearflag(inputState,PatientID),""):(setflag(inputState,PatientID) ,"Error"));
    ui->NameException->setText(
                (true == dcm->checkEachTag("PatientName",ui->Name->text().toStdString().c_str()))?
                    (clearflag(inputState,PatientName),""):(setflag(inputState,PatientName) ,"Error"));
    ui->AgeException->setText(
                (true == dcm->checkEachTag("PatientAge",ui->Age->text().toStdString().c_str()))?
                    (clearflag(inputState,PatientAge),""):(setflag(inputState,PatientAge) ,"Error"));
    ui->StudyDateException->setText(
                (true == dcm->checkEachTag("StudyDate",ui->StudyDate->text().toStdString().c_str()))?
                    (clearflag(inputState,StudyDate),""):(setflag(inputState,StudyDate) ,"Error"));
    ui->ContentDateException->setText(
                (true == dcm->checkEachTag("ContentDate",ui->ContentDate->text().toStdString().c_str()))?
                    (clearflag(inputState,ContentDate),""):(setflag(inputState,ContentDate) ,"Error"));
    if(inputState != 0)
        ui->btn_Save->setEnabled(false);
    else
        ui->btn_Save->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    if(dcm!=NULL)
        delete dcm;

    delete ui;
}
