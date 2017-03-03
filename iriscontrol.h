#ifndef IRISCONTROL_H
#define IRISCONTROL_H

#include <QtGui/QMainWindow>
#include "ui_iriscontrol.h"
#include <windows.h>
#include "Definitions.h"

class IRIScontrol : public QMainWindow
{
	Q_OBJECT

public:
	IRIScontrol(QWidget *parent = 0, Qt::WFlags flags = 0);
	~IRIScontrol();

	long    m_lActualValue;
	long    m_lStartPosition;
	long    m_lTargetPosition;

	BOOL OpenDevice();

private:
	Ui::IRIScontrolClass ui;
	HANDLE m_KeyHandle;
	WORD m_usNodeId;
	__int8 m_bMode;
	DWORD m_ulProfileVelocity;
	DWORD m_ulProfileAcceleration;
	DWORD m_ulProfileDeceleration;
	DWORD m_ulErrorCode;
	BOOL m_oUpdateActive;
	BOOL m_oInitialisation;
	BOOL m_oImmediately;

	BOOL ShowErrorInformation(DWORD p_ulErrorCode);

public slots:
	void doSomething();
};

#endif // IRISCONTROL_H
