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
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IRIScontrolClass
{
public:
    QWidget *centralWidget;
    QPushButton *testButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IRIScontrolClass)
    {
        if (IRIScontrolClass->objectName().isEmpty())
            IRIScontrolClass->setObjectName(QString::fromUtf8("IRIScontrolClass"));
        IRIScontrolClass->resize(444, 353);
        centralWidget = new QWidget(IRIScontrolClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        testButton = new QPushButton(centralWidget);
        testButton->setObjectName(QString::fromUtf8("testButton"));
        testButton->setGeometry(QRect(80, 90, 121, 61));
        IRIScontrolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IRIScontrolClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 444, 21));
        IRIScontrolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IRIScontrolClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        IRIScontrolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(IRIScontrolClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        IRIScontrolClass->setStatusBar(statusBar);

        retranslateUi(IRIScontrolClass);

        QMetaObject::connectSlotsByName(IRIScontrolClass);
    } // setupUi

    void retranslateUi(QMainWindow *IRIScontrolClass)
    {
        IRIScontrolClass->setWindowTitle(QApplication::translate("IRIScontrolClass", "IRIScontrol", 0, QApplication::UnicodeUTF8));
        testButton->setText(QApplication::translate("IRIScontrolClass", "Click to test!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IRIScontrolClass: public Ui_IRIScontrolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IRISCONTROL_H
