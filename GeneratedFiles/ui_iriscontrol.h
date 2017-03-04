/********************************************************************************
** Form generated from reading UI file 'iriscontrol.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IRISCONTROL_H
#define UI_IRISCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IRIScontrolClass
{
public:
    QWidget *centralWidget;
    QPushButton *testButton;
    QLineEdit *lineEdit;
    QPushButton *pBtnEnable;
    QPushButton *pBtnDisable;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QRadioButton *rBtnRelative;
    QRadioButton *rBtnAbsolute;
    QPushButton *pBtnMove;
    QFrame *line;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *IRIScontrolClass)
    {
        if (IRIScontrolClass->objectName().isEmpty())
            IRIScontrolClass->setObjectName(QString::fromUtf8("IRIScontrolClass"));
        IRIScontrolClass->resize(1053, 594);
        centralWidget = new QWidget(IRIScontrolClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        testButton = new QPushButton(centralWidget);
        testButton->setObjectName(QString::fromUtf8("testButton"));
        testButton->setGeometry(QRect(870, 40, 121, 61));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(870, 120, 113, 33));
        pBtnEnable = new QPushButton(centralWidget);
        pBtnEnable->setObjectName(QString::fromUtf8("pBtnEnable"));
        pBtnEnable->setGeometry(QRect(50, 70, 150, 46));
        pBtnDisable = new QPushButton(centralWidget);
        pBtnDisable->setObjectName(QString::fromUtf8("pBtnDisable"));
        pBtnDisable->setGeometry(QRect(50, 130, 150, 46));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 50, 151, 27));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(280, 90, 113, 33));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(410, 90, 92, 27));
        rBtnRelative = new QRadioButton(centralWidget);
        rBtnRelative->setObjectName(QString::fromUtf8("rBtnRelative"));
        rBtnRelative->setGeometry(QRect(280, 150, 160, 31));
        rBtnAbsolute = new QRadioButton(centralWidget);
        rBtnAbsolute->setObjectName(QString::fromUtf8("rBtnAbsolute"));
        rBtnAbsolute->setGeometry(QRect(280, 190, 160, 31));
        pBtnMove = new QPushButton(centralWidget);
        pBtnMove->setObjectName(QString::fromUtf8("pBtnMove"));
        pBtnMove->setGeometry(QRect(470, 80, 150, 46));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(50, 410, 641, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 450, 121, 27));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(210, 450, 113, 33));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(330, 450, 92, 27));
        IRIScontrolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IRIScontrolClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1053, 38));
        IRIScontrolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IRIScontrolClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        IRIScontrolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(IRIScontrolClass);
        QObject::connect(testButton, SIGNAL(clicked()), lineEdit, SLOT(clear()));

        QMetaObject::connectSlotsByName(IRIScontrolClass);
    } // setupUi

    void retranslateUi(QMainWindow *IRIScontrolClass)
    {
        IRIScontrolClass->setWindowTitle(QApplication::translate("IRIScontrolClass", "IRIScontrol", 0, QApplication::UnicodeUTF8));
        testButton->setText(QApplication::translate("IRIScontrolClass", "Click to test!", 0, QApplication::UnicodeUTF8));
        pBtnEnable->setText(QApplication::translate("IRIScontrolClass", "Enable", 0, QApplication::UnicodeUTF8));
        pBtnDisable->setText(QApplication::translate("IRIScontrolClass", "Disable", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IRIScontrolClass", "Target Position", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("IRIScontrolClass", "qc", 0, QApplication::UnicodeUTF8));
        rBtnRelative->setText(QApplication::translate("IRIScontrolClass", "Relative", 0, QApplication::UnicodeUTF8));
        rBtnAbsolute->setText(QApplication::translate("IRIScontrolClass", "Absolute", 0, QApplication::UnicodeUTF8));
        pBtnMove->setText(QApplication::translate("IRIScontrolClass", "Move", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("IRIScontrolClass", "Actual Value", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("IRIScontrolClass", "qc", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IRIScontrolClass: public Ui_IRIScontrolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IRISCONTROL_H
