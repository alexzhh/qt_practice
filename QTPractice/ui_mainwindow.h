/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave_As;
    QAction *actionQuit;
    QAction *actionEdit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *DCMPaint;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *Name;
    QLabel *NameException;
    QLabel *label_2;
    QLineEdit *Age;
    QLabel *AgeException;
    QLabel *label_3;
    QLineEdit *ID;
    QLabel *IDException;
    QLabel *label_4;
    QLineEdit *StudyData;
    QLabel *StudyDataException;
    QLabel *label_5;
    QLineEdit *ContentData;
    QLabel *ContentDataException;
    QPushButton *btn_Save;
    QPushButton *btn_Reset;
    QMenuBar *menuBar;
    QMenu *menuFile_F;
    QMenu *menuEdit_E;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(668, 418);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        actionEdit->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        DCMPaint = new QLabel(groupBox_2);
        DCMPaint->setObjectName(QStringLiteral("DCMPaint"));
        DCMPaint->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(DCMPaint);


        horizontalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Name = new QLineEdit(groupBox);
        Name->setObjectName(QStringLiteral("Name"));
        Name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(Name, 0, 1, 1, 2);

        NameException = new QLabel(groupBox);
        NameException->setObjectName(QStringLiteral("NameException"));

        gridLayout->addWidget(NameException, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        Age = new QLineEdit(groupBox);
        Age->setObjectName(QStringLiteral("Age"));

        gridLayout->addWidget(Age, 1, 1, 1, 2);

        AgeException = new QLabel(groupBox);
        AgeException->setObjectName(QStringLiteral("AgeException"));

        gridLayout->addWidget(AgeException, 1, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        ID = new QLineEdit(groupBox);
        ID->setObjectName(QStringLiteral("ID"));

        gridLayout->addWidget(ID, 2, 1, 1, 2);

        IDException = new QLabel(groupBox);
        IDException->setObjectName(QStringLiteral("IDException"));

        gridLayout->addWidget(IDException, 2, 3, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        StudyData = new QLineEdit(groupBox);
        StudyData->setObjectName(QStringLiteral("StudyData"));

        gridLayout->addWidget(StudyData, 3, 1, 1, 2);

        StudyDataException = new QLabel(groupBox);
        StudyDataException->setObjectName(QStringLiteral("StudyDataException"));

        gridLayout->addWidget(StudyDataException, 3, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        ContentData = new QLineEdit(groupBox);
        ContentData->setObjectName(QStringLiteral("ContentData"));

        gridLayout->addWidget(ContentData, 4, 1, 1, 2);

        ContentDataException = new QLabel(groupBox);
        ContentDataException->setObjectName(QStringLiteral("ContentDataException"));

        gridLayout->addWidget(ContentDataException, 4, 3, 1, 1);

        btn_Save = new QPushButton(groupBox);
        btn_Save->setObjectName(QStringLiteral("btn_Save"));

        gridLayout->addWidget(btn_Save, 5, 1, 1, 1);

        btn_Reset = new QPushButton(groupBox);
        btn_Reset->setObjectName(QStringLiteral("btn_Reset"));

        gridLayout->addWidget(btn_Reset, 5, 2, 1, 1);


        horizontalLayout->addWidget(groupBox);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 668, 21));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QStringLiteral("menuFile_F"));
        menuEdit_E = new QMenu(menuBar);
        menuEdit_E->setObjectName(QStringLiteral("menuEdit_E"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuEdit_E->menuAction());
        menuFile_F->addAction(actionOpen);
        menuFile_F->addAction(actionSave_As);
        menuFile_F->addSeparator();
        menuFile_F->addAction(actionQuit);
        menuEdit_E->addAction(actionEdit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DCM", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open(&O)", 0));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As(S)", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit(Q)", 0));
        actionEdit->setText(QApplication::translate("MainWindow", "Edit", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "DCM Image", 0));
        DCMPaint->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Patient Information", 0));
        label->setText(QApplication::translate("MainWindow", "\345\247\223 \345\220\215 \357\274\232", 0));
        NameException->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "\345\271\264 \351\276\204 \357\274\232", 0));
        AgeException->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "\347\227\205 \344\272\272 ID\357\274\232", 0));
        IDException->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "\346\243\200\346\237\245\346\227\266\351\227\264\357\274\232", 0));
        StudyDataException->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "\346\213\215\347\211\207\346\227\266\351\227\264\357\274\232", 0));
        ContentDataException->setText(QString());
        btn_Save->setText(QApplication::translate("MainWindow", "Save", 0));
        btn_Reset->setText(QApplication::translate("MainWindow", "Reset", 0));
        menuFile_F->setTitle(QApplication::translate("MainWindow", "File(&F)", 0));
        menuEdit_E->setTitle(QApplication::translate("MainWindow", "Edit(&E)", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
