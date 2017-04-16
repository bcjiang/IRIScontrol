#ifndef IRISCONTROL_H
#define IRISCONTROL_H

#include <QtGui/QMainWindow>
#include "ui_iriscontrol.h"
#include <windows.h>
#include "Definitions.h"
#include <atlstr.h>
#include <QTimer>
#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>

class IRIScontrol : public QMainWindow
{
	Q_OBJECT

public:
	IRIScontrol(QWidget *parent = 0, Qt::WFlags flags = 0);
	~IRIScontrol();

	long    m_lActualValue;
	long    m_lActualValue2;
	long    m_lActualValue3;
	long    m_lActualValue4;
	long    m_lStartPosition;
	long    m_lStartPosition2;
	long    m_lStartPosition3;
	long    m_lStartPosition4;
	long    m_lTargetPosition;
	long    m_lTargetPosition2;
	long    m_lTargetPosition3;
	long    m_lTargetPosition4;
	long    m_lTargetPoseRoll;
	hduVector3Dd m_lGimbalJointPosition;
	CString m_strNodeId;
	int     m_oRadio;
	QTimer *timer;

	BOOL OpenDevice();

	void UpdateNodeIdString();

private:
	Ui::IRIScontrolClass ui;
	HANDLE m_KeyHandle;
	WORD m_usNodeId;
	WORD m_usNodeId2;
	WORD m_usNodeId3;
	WORD m_usNodeId4;
	__int8 m_bMode;
	DWORD m_ulProfileVelocity;
	DWORD m_ulProfileAcceleration;
	DWORD m_ulProfileDeceleration;
	DWORD m_ulErrorCode;
	BOOL m_oUpdateActive;
	BOOL m_oInitialisation;
	BOOL m_oImmediately;
	BOOL m_oTeleopActive;

	BOOL ShowErrorInformation(DWORD p_ulErrorCode);

public slots:
	void OnButtonEnable();
	void OnButtonDisable();
	void OnButtonEnableTeleop();
	void OnButtonMove();
	void OnButtonMoveToPose();
	void OnRadioRelative();
	void OnRadioAbsolute();
	void UpdateTargetPositionText(QString text);
	void UpdateTargetPositionText2(QString text);
	void UpdateTargetRollText(QString);
	BOOL UpdateStatus();

};


#endif // IRISCONTROL_H
