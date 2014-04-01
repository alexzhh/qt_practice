#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QObject::connect(ui->actionQuit,SIGNAL(triggered()),SLOT(QuitWindows()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
