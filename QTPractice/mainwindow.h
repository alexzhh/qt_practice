#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QTextDecoder>
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
public slots:
    void QuitWindows()
    {
        if(QMessageBox::warning(this,QString::fromStdString("Warning"),
                                QString::fromStdString("Quit Windows?"),
                                QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        {
            emit close();
        }
    }
};

#endif // MAINWINDOW_H
