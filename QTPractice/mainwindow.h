#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QTextDecoder>
#include <QFile>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <string>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString OpenFilePath;
    QString SaveFilePath;
public slots:
    void OpenFile();
    void SaveFile();
    void QuitWindows();
    void EditModeChanged(bool);
};

#endif // MAINWINDOW_H
