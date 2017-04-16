#include "iriscontrol.h"
#include <math.h>

#define PI 3.14159265

IRIScontrol::IRIScontrol(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	, m_strNodeId(_T("1"))
	, m_oRadio(0)
	, m_lStartPosition(0)
	, m_lStartPosition2(0)
	, m_lStartPosition3(0)
	, m_lStartPosition4(0)
	, m_lTargetPosition(2000)
	, m_lTargetPosition2(2000)
	, m_lTargetPosition3(2000)
	, m_lTargetPosition4(2000)
	, m_lTargetPoseRoll(0)
	, m_lGimbalJointPosition(0.0,0.0,0.0)
{
	ui.setupUi(this);
	connect(ui.pBtnEnable,SIGNAL(clicked()),this,SLOT(OnButtonEnable()));
	connect(ui.pBtnDisable,SIGNAL(clicked()),this,SLOT(OnButtonDisable()));
	connect(ui.pBtnEnableTeleop,SIGNAL(clicked()),this,SLOT(OnButtonEnableTeleop()));
	connect(ui.eTargetPosition,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetPositionText(QString)));
	connect(ui.eTargetPosition2,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetPositionText2(QString)));
	connect(ui.eTargetRoll,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetRollText(QString)));
	connect(ui.pBtnMove,SIGNAL(clicked()),this,SLOT(OnButtonMove()));
	connect(ui.pBtnMoveToPose,SIGNAL(clicked()),this,SLOT(OnButtonMoveToPose()));
	connect(ui.rBtnRelative,SIGNAL(clicked()),this,SLOT(OnRadioRelative()));
	connect(ui.rBtnAbsolute,SIGNAL(clicked()),this,SLOT(OnRadioAbsolute()));

	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(UpdateStatus()));
	
}

IRIScontrol::~IRIScontrol()
{

}

BOOL IRIScontrol::OpenDevice()
{
	m_oImmediately = TRUE;
	m_oUpdateActive = FALSE;
	m_oTeleopActive = FALSE;
	m_usNodeId = 1;
	m_usNodeId2 = 2;
	m_usNodeId3 = 3;
	m_usNodeId4 = 4;

	HANDLE hNewKeyHandle;

	hNewKeyHandle = VCS_OpenDeviceDlg(&m_ulErrorCode);
	if(hNewKeyHandle)
	{
		m_KeyHandle = hNewKeyHandle;

		//Clear Error History
		if(VCS_ClearFault(m_KeyHandle, m_usNodeId, &m_ulErrorCode)
			&& VCS_ClearFault(m_KeyHandle, m_usNodeId2, &m_ulErrorCode)
			&& VCS_ClearFault(m_KeyHandle, m_usNodeId3, &m_ulErrorCode)
			&& VCS_ClearFault(m_KeyHandle, m_usNodeId4, &m_ulErrorCode))
		{
			//Read Operation Mode
			if(VCS_GetOperationMode(m_KeyHandle, m_usNodeId, &m_bMode, &m_ulErrorCode)
				&& VCS_GetOperationMode(m_KeyHandle, m_usNodeId2, &m_bMode, &m_ulErrorCode)
				&& VCS_GetOperationMode(m_KeyHandle, m_usNodeId3, &m_bMode, &m_ulErrorCode)
				&& VCS_GetOperationMode(m_KeyHandle, m_usNodeId4, &m_bMode, &m_ulErrorCode))
			{
				//Read Position Profile Objects
				if(VCS_GetPositionProfile(m_KeyHandle, m_usNodeId, &m_ulProfileVelocity, &m_ulProfileAcceleration, &m_ulProfileDeceleration, &m_ulErrorCode)
					&& VCS_GetPositionProfile(m_KeyHandle, m_usNodeId2, &m_ulProfileVelocity, &m_ulProfileAcceleration, &m_ulProfileDeceleration, &m_ulErrorCode)
					&& VCS_GetPositionProfile(m_KeyHandle, m_usNodeId3, &m_ulProfileVelocity, &m_ulProfileAcceleration, &m_ulProfileDeceleration, &m_ulErrorCode)
					&& VCS_GetPositionProfile(m_KeyHandle, m_usNodeId4, &m_ulProfileVelocity, &m_ulProfileAcceleration, &m_ulProfileDeceleration, &m_ulErrorCode))
				{
					//Write Profile Position Mode
					if(VCS_SetOperationMode(m_KeyHandle, m_usNodeId, OMD_PROFILE_POSITION_MODE, &m_ulErrorCode)
						&& VCS_SetOperationMode(m_KeyHandle, m_usNodeId2, OMD_PROFILE_POSITION_MODE, &m_ulErrorCode)
						&& VCS_SetOperationMode(m_KeyHandle, m_usNodeId3, OMD_PROFILE_POSITION_MODE, &m_ulErrorCode)
						&& VCS_SetOperationMode(m_KeyHandle, m_usNodeId4, OMD_PROFILE_POSITION_MODE, &m_ulErrorCode))
					{
						//Write Profile Position Objects
						if(VCS_SetPositionProfile(m_KeyHandle, m_usNodeId, 1000, 10000, 10000, &m_ulErrorCode)
							&& VCS_SetPositionProfile(m_KeyHandle, m_usNodeId2, 1000, 10000, 10000, &m_ulErrorCode)
							&& VCS_SetPositionProfile(m_KeyHandle, m_usNodeId3, 1000, 10000, 10000, &m_ulErrorCode)
							&& VCS_SetPositionProfile(m_KeyHandle, m_usNodeId4, 1000, 10000, 10000, &m_ulErrorCode))
						{
							//Read Actual Position
							if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId, &m_lStartPosition, &m_ulErrorCode)
								&& VCS_GetPositionIs(m_KeyHandle, m_usNodeId2, &m_lStartPosition2, &m_ulErrorCode)
								&& VCS_GetPositionIs(m_KeyHandle, m_usNodeId3, &m_lStartPosition3, &m_ulErrorCode)
								&& VCS_GetPositionIs(m_KeyHandle, m_usNodeId4, &m_lStartPosition4, &m_ulErrorCode))
							{

								return TRUE;
							}
						}
					}
				}
			}
		}
		ShowErrorInformation(m_ulErrorCode);
		MessageBox(NULL,(LPCWSTR)L"Test Message",(LPCWSTR)L"Test Message Window",MB_CANCELTRYCONTINUE);
	}
	return FALSE;
}

BOOL IRIScontrol::ShowErrorInformation(DWORD p_ulErrorCode)
{
    char* pStrErrorInfo;
    CString strDescription;

    if((pStrErrorInfo = (char*)malloc(100)) == NULL)
    {
        MessageBox(NULL,(LPCWSTR)L"Not enough memory to allocate buffer for error information string\n",(LPCWSTR)L"System Error",MB_OK);

        return FALSE;
    }

    if(VCS_GetErrorInfo(p_ulErrorCode, pStrErrorInfo, 100))
    {
        strDescription = pStrErrorInfo;
		MessageBox(NULL,(LPCWSTR)strDescription,(LPCWSTR)L"System Error",MB_OK);
        //AfxMessageBox(strDescription, MB_ICONINFORMATION);

        free(pStrErrorInfo);

        return TRUE;
    }
    else
    {
        free(pStrErrorInfo);
		MessageBox(NULL,(LPCWSTR)L"Error information can't be read!",(LPCWSTR)L"System Error",MB_OK);

        return FALSE;
    }
}

void IRIScontrol::OnButtonEnable()
{
	BOOL oFault = FALSE;

    UpdateNodeIdString();

    if(!VCS_GetFaultState(m_KeyHandle, m_usNodeId, &oFault, &m_ulErrorCode)
		|| !VCS_GetFaultState(m_KeyHandle, m_usNodeId2, &oFault, &m_ulErrorCode)
		|| !VCS_GetFaultState(m_KeyHandle, m_usNodeId3, &oFault, &m_ulErrorCode)
		|| !VCS_GetFaultState(m_KeyHandle, m_usNodeId4, &oFault, &m_ulErrorCode))
    {
        ShowErrorInformation(m_ulErrorCode);
        return;
    }

    if(oFault)
    {
        if(!VCS_ClearFault(m_KeyHandle, m_usNodeId, &m_ulErrorCode)
			|| !VCS_ClearFault(m_KeyHandle, m_usNodeId2, &m_ulErrorCode)
			|| !VCS_ClearFault(m_KeyHandle, m_usNodeId3, &m_ulErrorCode)
			|| !VCS_ClearFault(m_KeyHandle, m_usNodeId4, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
            return;
        }
    }

    if(!VCS_SetEnableState(m_KeyHandle, m_usNodeId, &m_ulErrorCode)
		|| !VCS_SetEnableState(m_KeyHandle, m_usNodeId2, &m_ulErrorCode)
		|| !VCS_SetEnableState(m_KeyHandle, m_usNodeId3, &m_ulErrorCode)
		|| !VCS_SetEnableState(m_KeyHandle, m_usNodeId4, &m_ulErrorCode))
    {
        ShowErrorInformation(m_ulErrorCode);
		return;
    }

	MessageBox(NULL,(LPCWSTR)L"Successfully enabled!",(LPCWSTR)L"System Message",MB_OK);
	ui.pBtnDisable->setEnabled(TRUE);
	timer->start(100);
	m_oUpdateActive = TRUE;

	// Enable Phantom Omni device
	HHD hHD;
	hHD = hdInitDevice(HD_DEFAULT_DEVICE);
	hdStartScheduler();
}

void IRIScontrol::OnButtonDisable()
{
    UpdateNodeIdString();

    if(!VCS_SetDisableState(m_KeyHandle, m_usNodeId, &m_ulErrorCode)
		|| !VCS_SetDisableState(m_KeyHandle, m_usNodeId2, &m_ulErrorCode)
		|| !VCS_SetDisableState(m_KeyHandle, m_usNodeId3, &m_ulErrorCode)
		|| !VCS_SetDisableState(m_KeyHandle, m_usNodeId4, &m_ulErrorCode))
    {
        ShowErrorInformation(m_ulErrorCode);
    }

	MessageBox(NULL,(LPCWSTR)L"Controllers disabled!",(LPCWSTR)L"System Message",MB_OK);
	ui.pBtnDisable->setEnabled(FALSE);
}

void IRIScontrol::OnButtonEnableTeleop()
{
	if(m_oTeleopActive == FALSE){m_oTeleopActive = TRUE;}
	else{m_oTeleopActive = FALSE;}
}

void IRIScontrol::UpdateNodeIdString()
{
    const size_t size(3);

    char strNodeId[size];

    _itoa(m_usNodeId, strNodeId, 10);
    m_strNodeId = strNodeId;
}

void IRIScontrol::OnButtonMove()  
{
    UpdateNodeIdString();

    if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId, &m_lStartPosition, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId, m_lTargetPosition, m_oRadio, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }

	if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId2, &m_lStartPosition2, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId2, m_lTargetPosition2, m_oRadio, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }

	if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId3, &m_lStartPosition3, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId3, m_lTargetPosition3, m_oRadio, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }

	if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId4, &m_lStartPosition4, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId4, m_lTargetPosition4, m_oRadio, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }

    UpdateStatus();
}

void IRIScontrol::OnButtonMoveToPose()  
{
    UpdateNodeIdString();

	// This part convert target pose into target motor rotation angles (qc)
    //m_lTargetPosition = 983040 * (0.8268 - cos(0.5974 - (m_lTargetPoseRoll * PI / 180)/24));
	//m_lTargetPosition2 = 983040 * (0.8268 - cos(0.5974 + (m_lTargetPoseRoll * PI / 180)/24));
	if(m_lTargetPoseRoll >= 0){
	m_lTargetPosition = -1.778 * pow((double)m_lTargetPoseRoll,3) + 28.1 * pow((double)m_lTargetPoseRoll,2) + 5018 * m_lTargetPoseRoll;
	m_lTargetPosition2 = - m_lTargetPosition / 2;
	}
	else {
		m_lTargetPosition2 = -1.778 * pow((double)m_lTargetPoseRoll,3) + 28.1 * pow((double)m_lTargetPoseRoll,2) + 5018 * m_lTargetPoseRoll;
		m_lTargetPosition = - m_lTargetPosition2 / 2;
	}
	//-----------------------------------------------------------------

    if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId, &m_lStartPosition, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId, m_lTargetPosition, 1, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }

	if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId2, &m_lStartPosition2, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId2, m_lTargetPosition2, 1, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }

    UpdateStatus();
}


void IRIScontrol::OnRadioRelative()
{
	m_oRadio = 0;
}

void IRIScontrol::OnRadioAbsolute()
{
	m_oRadio = 1;
}

BOOL IRIScontrol::UpdateStatus()
{
    BOOL oEnable = TRUE;
    BOOL oResult = m_oUpdateActive;

	// Update the Current Position
    if(oResult)
    {
        oResult = VCS_GetPositionIs(m_KeyHandle, m_usNodeId, &m_lActualValue, &m_ulErrorCode); 
		ui.eTruePosition->setText(QString::number(m_lActualValue));
        if(!oResult)
        {
			timer->stop();
            ShowErrorInformation(m_ulErrorCode);

            m_lActualValue = 0;
            m_lStartPosition = 0;
        }
		oResult = VCS_GetPositionIs(m_KeyHandle, m_usNodeId2, &m_lActualValue2, &m_ulErrorCode); 
		ui.eTruePosition2->setText(QString::number(m_lActualValue2));
        if(!oResult)
        {
			timer->stop();
            ShowErrorInformation(m_ulErrorCode);

            m_lActualValue2 = 0;
            m_lStartPosition2 = 0;
        }
        oResult = VCS_GetPositionIs(m_KeyHandle, m_usNodeId3, &m_lActualValue3, &m_ulErrorCode); 
		ui.eTruePosition3->setText(QString::number(m_lActualValue3));
        if(!oResult)
        {
			timer->stop();
            ShowErrorInformation(m_ulErrorCode);

            m_lActualValue3 = 0;
            m_lStartPosition3 = 0;
        }
        oResult = VCS_GetPositionIs(m_KeyHandle, m_usNodeId4, &m_lActualValue4, &m_ulErrorCode); 
		ui.eTruePosition4->setText(QString::number(m_lActualValue4));
        if(!oResult)
        {
			timer->stop();
            ShowErrorInformation(m_ulErrorCode);

            m_lActualValue4 = 0;
            m_lStartPosition4 = 0;
        }

		if(m_oTeleopActive == TRUE){
			//MessageBox(NULL,(LPCWSTR)L"Enabled teleoperation!",(LPCWSTR)L"System Message",MB_OK);
			hdBeginFrame(hdGetCurrentDevice());
			hdGetDoublev(HD_CURRENT_GIMBAL_ANGLES, m_lGimbalJointPosition);
			hdEndFrame(hdGetCurrentDevice());
			ui.eMasterPosition->setText(QString::number(m_lGimbalJointPosition[0]));
			m_lTargetPoseRoll = (m_lGimbalJointPosition[0] + 0.15)/0.5 * 30;
			
			if(m_lTargetPoseRoll >= 0){
			m_lTargetPosition = -1.778 * pow((double)m_lTargetPoseRoll,3) + 28.1 * pow((double)m_lTargetPoseRoll,2) + 5018 * m_lTargetPoseRoll;
			m_lTargetPosition2 = - m_lTargetPosition / 2;
			}
			else {
			m_lTargetPosition2 = -1.778 * pow((double)m_lTargetPoseRoll,3) + 28.1 * pow((double)m_lTargetPoseRoll,2) + 5018 * m_lTargetPoseRoll;
			m_lTargetPosition = - m_lTargetPosition2 / 2;
			}
			if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId, m_lTargetPosition, 1, m_oImmediately, &m_ulErrorCode))
			{
            ShowErrorInformation(m_ulErrorCode);
			}

			if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId2, m_lTargetPosition2, 1, m_oImmediately, &m_ulErrorCode))
			{
            ShowErrorInformation(m_ulErrorCode);
			}
		}
		else{
			//MessageBox(NULL,(LPCWSTR)L"Disabled teleoperation!",(LPCWSTR)L"System Message",MB_OK);
			ui.eMasterPosition->setText(QString::number(0));
		}
    }
    else
    {
        m_lActualValue = 0;
		m_lActualValue2 = 0;
		m_lActualValue3 = 0;
		m_lActualValue4 = 0;
        m_lStartPosition = 0;
		m_lStartPosition2 = 0;
		m_lStartPosition3 = 0;
		m_lStartPosition4 = 0;
    }

    //if(m_hWnd) UpdateData(false);

    //return oResult;	
	//MessageBox(NULL,(LPCWSTR)L"UpdateStatus() called",(LPCWSTR)L"System Message",MB_OK);
	return TRUE;
}

void IRIScontrol::UpdateTargetPositionText(QString text)
{
	m_lTargetPosition = text.toLong();
}

void IRIScontrol::UpdateTargetPositionText2(QString text)
{
	m_lTargetPosition2 = text.toLong();
}

void IRIScontrol::UpdateTargetRollText(QString text)
{
	m_lTargetPoseRoll = text.toLong();
}