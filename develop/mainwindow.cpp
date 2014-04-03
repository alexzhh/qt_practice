#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionQuit,SIGNAL(triggered()),SLOT(QuitWindows()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),SLOT(OpenFile()));
    QObject::connect(ui->actionSave_As,SIGNAL(triggered()),SLOT(SaveFile()));
    QObject::connect(ui->actionEdit,SIGNAL(triggered(bool)),this,SLOT(EditModeChanged(bool)));
    emit EditModeChanged(false);
    //QMessageBox::about(NULL,"",QString::number(ui->tableWidget->rowCount())+QString::number(ui->tableWidget->columnCount()));

    dcm = new DcmInformation();
}
void MainWindow::OpenFile()
{
    OpenFilePath = QFileDialog::getOpenFileName(this,QString::fromStdString("打开DCM文件"),QDir::currentPath(),"DCM文件(*.dcm)");
    //QMessageBox::about(NULL,"",OpenFilePath);
    dcm->openDcmFile(OpenFilePath);
//    QVector<AttrElements> tmp = dcm->getAttributes();
//    QMessageBox::information(this,"",tmp.at(0).value+tmp.at(0).vr);
    ui->paint->setPixmap( dcm->drawDcmImage(OpenFilePath));

}

void MainWindow::SaveFile()
{
    SaveFilePath = QFileDialog::getSaveFileName(this,QString::fromStdString(""),QDir::currentPath(),"DCM文件(*.dcm)");
    QMessageBox::about(NULL,"",SaveFilePath);
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
        ui->buttonBox->setHidden(false);
    }
    else
    {
        ui->buttonBox->setHidden(true);

    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dcm;
}
