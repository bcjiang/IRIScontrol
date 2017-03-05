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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IRIScontrolClass
{
public:
    QWidget *centralWidget;
    QPushButton *pBtnEnable;
    QPushButton *pBtnDisable;
    QLabel *label;
    QLineEdit *eTargetPosition;
    QLabel *label_2;
    QRadioButton *rBtnRelative;
    QRadioButton *rBtnAbsolute;
    QPushButton *pBtnMove;
    QFrame *line;
    QLabel *label_3;
    QLineEdit *eTruePosition;
    QLabel *label_4;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *IRIScontrolClass)
    {
        if (IRIScontrolClass->objectName().isEmpty())
            IRIScontrolClass->setObjectName(QString::fromUtf8("IRIScontrolClass"));
        IRIScontrolClass->resize(509, 436);
        IRIScontrolClass->setStyleSheet(QString::fromUtf8("#centralWidget {\n"
"border: 3px solid gray;\n"
"border-radius: 40px;\n"
"background: white;\n"
"}\n"
""));
        centralWidget = new QWidget(IRIScontrolClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pBtnEnable = new QPushButton(centralWidget);
        pBtnEnable->setObjectName(QString::fromUtf8("pBtnEnable"));
        pBtnEnable->setGeometry(QRect(50, 70, 150, 46));
        pBtnDisable = new QPushButton(centralWidget);
        pBtnDisable->setObjectName(QString::fromUtf8("pBtnDisable"));
        pBtnDisable->setEnabled(false);
        pBtnDisable->setGeometry(QRect(50, 130, 150, 46));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 70, 151, 27));
        eTargetPosition = new QLineEdit(centralWidget);
        eTargetPosition->setObjectName(QString::fromUtf8("eTargetPosition"));
        eTargetPosition->setGeometry(QRect(260, 110, 113, 33));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(390, 110, 71, 27));
        rBtnRelative = new QRadioButton(centralWidget);
        rBtnRelative->setObjectName(QString::fromUtf8("rBtnRelative"));
        rBtnRelative->setGeometry(QRect(260, 170, 160, 31));
        rBtnRelative->setChecked(true);
        rBtnAbsolute = new QRadioButton(centralWidget);
        rBtnAbsolute->setObjectName(QString::fromUtf8("rBtnAbsolute"));
        rBtnAbsolute->setGeometry(QRect(260, 210, 160, 31));
        pBtnMove = new QPushButton(centralWidget);
        pBtnMove->setObjectName(QString::fromUtf8("pBtnMove"));
        pBtnMove->setGeometry(QRect(50, 190, 150, 46));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(30, 300, 441, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 330, 121, 27));
        eTruePosition = new QLineEdit(centralWidget);
        eTruePosition->setObjectName(QString::fromUtf8("eTruePosition"));
        eTruePosition->setEnabled(true);
        eTruePosition->setGeometry(QRect(210, 330, 113, 33));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(330, 330, 92, 27));
        IRIScontrolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IRIScontrolClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 509, 21));
        IRIScontrolClass->setMenuBar(menuBar);

        retranslateUi(IRIScontrolClass);

        QMetaObject::connectSlotsByName(IRIScontrolClass);
    } // setupUi

    void retranslateUi(QMainWindow *IRIScontrolClass)
    {
        IRIScontrolClass->setWindowTitle(QApplication::translate("IRIScontrolClass", "IRIScontrol", 0, QApplication::UnicodeUTF8));
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
