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
    emit EditModeChanged(false);
    //QMessageBox::about(NULL,"",QString::number(ui->tableWidget->rowCount())+QString::number(ui->tableWidget->columnCount()));

}
void MainWindow::OpenFile()
{
    QString OpenFilePath = QFileDialog::getOpenFileName(this,QString::fromStdString("打开DCM文件"),QDir::currentPath(),"DCM文件(*.dcm)");
        if(OpenFilePath!="")
        {
            QMessageBox::about(NULL,"",OpenFilePath);
            //Do FileOpen
        }

}

void MainWindow::SaveFile()
{
    QString SaveFilePath = QFileDialog::getSaveFileName(this,QString::fromStdString(""),QDir::currentPath(),"DCM文件(*.dcm)");
        if(SaveFilePath!="")
        {
            QMessageBox::about(NULL,"",SaveFilePath);
            //Do Save File
        }

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
}
