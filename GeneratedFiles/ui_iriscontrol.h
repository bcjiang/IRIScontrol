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
    QLabel *label_5;
    QLabel *label_9;
    QLineEdit *eTargetPosition2;
    QLineEdit *eTruePosition2;
    QLineEdit *eTargetRoll;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pBtnMoveToPose;
    QPushButton *pBtnEnableTeleop;
    QLineEdit *eMasterPosition;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_12;
    QLineEdit *eTargetPosition3;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *eTargetPosition4;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *eTruePosition3;
    QLineEdit *eTruePosition4;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *eTargetPitch;
    QLabel *label_22;
    QLineEdit *eMasterPosition2;
    QLabel *label_23;
    QLabel *label_24;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *IRIScontrolClass)
    {
        if (IRIScontrolClass->objectName().isEmpty())
            IRIScontrolClass->setObjectName(QString::fromUtf8("IRIScontrolClass"));
        IRIScontrolClass->resize(635, 461);
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
        pBtnEnable->setGeometry(QRect(50, 40, 150, 46));
        pBtnDisable = new QPushButton(centralWidget);
        pBtnDisable->setObjectName(QString::fromUtf8("pBtnDisable"));
        pBtnDisable->setEnabled(false);
        pBtnDisable->setGeometry(QRect(50, 100, 150, 46));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 50, 151, 27));
        eTargetPosition = new QLineEdit(centralWidget);
        eTargetPosition->setObjectName(QString::fromUtf8("eTargetPosition"));
        eTargetPosition->setGeometry(QRect(280, 90, 111, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(410, 90, 71, 27));
        rBtnRelative = new QRadioButton(centralWidget);
        rBtnRelative->setObjectName(QString::fromUtf8("rBtnRelative"));
        rBtnRelative->setGeometry(QRect(240, 290, 81, 31));
        rBtnRelative->setChecked(true);
        rBtnAbsolute = new QRadioButton(centralWidget);
        rBtnAbsolute->setObjectName(QString::fromUtf8("rBtnAbsolute"));
        rBtnAbsolute->setGeometry(QRect(340, 290, 101, 31));
        pBtnMove = new QPushButton(centralWidget);
        pBtnMove->setObjectName(QString::fromUtf8("pBtnMove"));
        pBtnMove->setGeometry(QRect(50, 160, 150, 51));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(30, 340, 561, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 370, 121, 27));
        eTruePosition = new QLineEdit(centralWidget);
        eTruePosition->setObjectName(QString::fromUtf8("eTruePosition"));
        eTruePosition->setEnabled(true);
        eTruePosition->setGeometry(QRect(130, 370, 81, 33));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(220, 370, 21, 27));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(230, 100, 46, 13));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(150, 410, 46, 13));
        eTargetPosition2 = new QLineEdit(centralWidget);
        eTargetPosition2->setObjectName(QString::fromUtf8("eTargetPosition2"));
        eTargetPosition2->setGeometry(QRect(280, 140, 111, 31));
        eTruePosition2 = new QLineEdit(centralWidget);
        eTruePosition2->setObjectName(QString::fromUtf8("eTruePosition2"));
        eTruePosition2->setGeometry(QRect(250, 370, 81, 31));
        eTargetRoll = new QLineEdit(centralWidget);
        eTargetRoll->setObjectName(QString::fromUtf8("eTargetRoll"));
        eTargetRoll->setGeometry(QRect(450, 60, 111, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(450, 30, 121, 16));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(450, 100, 141, 16));
        pBtnMoveToPose = new QPushButton(centralWidget);
        pBtnMoveToPose->setObjectName(QString::fromUtf8("pBtnMoveToPose"));
        pBtnMoveToPose->setGeometry(QRect(50, 260, 151, 51));
        pBtnEnableTeleop = new QPushButton(centralWidget);
        pBtnEnableTeleop->setObjectName(QString::fromUtf8("pBtnEnableTeleop"));
        pBtnEnableTeleop->setGeometry(QRect(450, 180, 121, 41));
        eMasterPosition = new QLineEdit(centralWidget);
        eMasterPosition->setObjectName(QString::fromUtf8("eMasterPosition"));
        eMasterPosition->setGeometry(QRect(450, 300, 111, 31));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(450, 230, 141, 16));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(230, 150, 41, 16));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(410, 140, 31, 16));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(270, 410, 46, 13));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(340, 380, 21, 16));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(230, 200, 46, 13));
        eTargetPosition3 = new QLineEdit(centralWidget);
        eTargetPosition3->setObjectName(QString::fromUtf8("eTargetPosition3"));
        eTargetPosition3->setGeometry(QRect(280, 190, 111, 31));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(410, 190, 21, 16));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(230, 250, 46, 13));
        eTargetPosition4 = new QLineEdit(centralWidget);
        eTargetPosition4->setObjectName(QString::fromUtf8("eTargetPosition4"));
        eTargetPosition4->setGeometry(QRect(280, 240, 111, 31));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(410, 250, 46, 13));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(390, 410, 46, 13));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(510, 410, 46, 13));
        eTruePosition3 = new QLineEdit(centralWidget);
        eTruePosition3->setObjectName(QString::fromUtf8("eTruePosition3"));
        eTruePosition3->setGeometry(QRect(370, 370, 81, 31));
        eTruePosition4 = new QLineEdit(centralWidget);
        eTruePosition4->setObjectName(QString::fromUtf8("eTruePosition4"));
        eTruePosition4->setGeometry(QRect(490, 370, 81, 31));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(460, 380, 21, 16));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(580, 380, 21, 16));
        eTargetPitch = new QLineEdit(centralWidget);
        eTargetPitch->setObjectName(QString::fromUtf8("eTargetPitch"));
        eTargetPitch->setGeometry(QRect(450, 120, 111, 31));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(450, 160, 131, 16));
        eMasterPosition2 = new QLineEdit(centralWidget);
        eMasterPosition2->setObjectName(QString::fromUtf8("eMasterPosition2"));
        eMasterPosition2->setGeometry(QRect(450, 260, 111, 31));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(570, 310, 31, 20));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(570, 270, 46, 13));
        IRIScontrolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IRIScontrolClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 635, 21));
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
        label_5->setText(QApplication::translate("IRIScontrolClass", "Node1", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("IRIScontrolClass", "Node1", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("IRIScontrolClass", "Target IRIS Orientation", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("IRIScontrolClass", "Roll Angle (0~20)", 0, QApplication::UnicodeUTF8));
        pBtnMoveToPose->setText(QApplication::translate("IRIScontrolClass", "Move to Pose", 0, QApplication::UnicodeUTF8));
        pBtnEnableTeleop->setText(QApplication::translate("IRIScontrolClass", "Enable Teleoperation", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("IRIScontrolClass", "Phantom Omni Angle: (deg)", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("IRIScontrolClass", "Node2", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("IRIScontrolClass", "qc", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("IRIScontrolClass", "Node2", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("IRIScontrolClass", "qc", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("IRIScontrolClass", "Node3", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("IRIScontrolClass", "qc", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("IRIScontrolClass", "Node4", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("IRIScontrolClass", "qc", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("IRIScontrolClass", "Node3", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("IRIScontrolClass", "Node4", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("IRIScontrolClass", "qc", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("IRIScontrolClass", "qc", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("IRIScontrolClass", "Pitch Angle (-20 ~ 20 deg)", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("IRIScontrolClass", "Pitch", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("IRIScontrolClass", "Roll", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IRIScontrolClass: public Ui_IRIScontrolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IRISCONTROL_H
