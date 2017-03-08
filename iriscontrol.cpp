#include "iriscontrol.h"

IRIScontrol::IRIScontrol(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	, m_strNodeId(_T("1"))
	, m_oRadio(0)
	, m_lStartPosition(0)
	, m_lTargetPosition(2000)
	, m_lTargetPosition2(2000)
{
	ui.setupUi(this);
	connect(ui.pBtnEnable,SIGNAL(clicked()),this,SLOT(OnButtonEnable()));
	connect(ui.eTargetPosition,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetPositionText(QString)));
	connect(ui.eTargetPosition2,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetPositionText2(QString)));
	connect(ui.pBtnMove,SIGNAL(clicked()),this,SLOT(OnButtonMove()));
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
	m_usNodeId = 1;

	HANDLE hNewKeyHandle;

	hNewKeyHandle = VCS_OpenDeviceDlg(&m_ulErrorCode);
	if(hNewKeyHandle)
	{
		m_KeyHandle = hNewKeyHandle;

		//Clear Error History
		if(VCS_ClearFault(m_KeyHandle, m_usNodeId, &m_ulErrorCode))
		{
			//Read Operation Mode
			if(VCS_GetOperationMode(m_KeyHandle, m_usNodeId, &m_bMode, &m_ulErrorCode))
			{
				//Read Position Profile Objects
				if(VCS_GetPositionProfile(m_KeyHandle, m_usNodeId, &m_ulProfileVelocity, &m_ulProfileAcceleration, &m_ulProfileDeceleration, &m_ulErrorCode))
				{
					//Write Profile Position Mode
					if(VCS_SetOperationMode(m_KeyHandle, m_usNodeId, OMD_PROFILE_POSITION_MODE, &m_ulErrorCode))
					{
						//Write Profile Position Objects
						if(VCS_SetPositionProfile(m_KeyHandle, m_usNodeId, 100, 1000, 1000, &m_ulErrorCode))
						{
							//Read Actual Position
							if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId, &m_lStartPosition, &m_ulErrorCode))
							{

								return TRUE;
							}
						}
					}
				}
			}
		}
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

    if(!VCS_GetFaultState(m_KeyHandle, m_usNodeId, &oFault, &m_ulErrorCode))
    {
        ShowErrorInformation(m_ulErrorCode);
        return;
    }

    if(oFault)
    {
        if(!VCS_ClearFault(m_KeyHandle, m_usNodeId, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
            return;
        }
    }

    if(!VCS_SetEnableState(m_KeyHandle, m_usNodeId, &m_ulErrorCode))
    {
        ShowErrorInformation(m_ulErrorCode);
    }

	MessageBox(NULL,(LPCWSTR)L"Successfully enabled!",(LPCWSTR)L"System Message",MB_OK);
	ui.pBtnDisable->setEnabled(TRUE);
	timer->start(100);
	m_oUpdateActive = TRUE;
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

    //if(m_oRadio == 0)
    //{
    //    m_Move.SetWindowText("&Move Relative");
    //}
    //else
    //{
    //    m_Move.SetWindowText("&Move Absolute");
    //}

    //if(oResult)
    //{
    //    oResult = VCS_GetOperationMode(m_KeyHandle, m_usNodeId, &m_bMode, &m_ulErrorCode);
    //    if(oResult)
    //    {
    //        switch(m_bMode)
    //        {
    //            case -6: m_strActiveMode = "Step/Direction Mode"; break;
    //            case -5: m_strActiveMode = "Master Encoder Mode"; break;
    //            case -3: m_strActiveMode = "Current Mode"; break;
    //            case -2: m_strActiveMode = "Velocity Mode"; break;
    //            case -1: m_strActiveMode = "Position Mode"; break;
    //            case 1: m_strActiveMode = "Profile Position Mode"; break;
    //            case 3: m_strActiveMode = "Profile Velocity Mode"; break;
    //            case 6: m_strActiveMode = "Homing Mode"; break;
    //            case 7: m_strActiveMode = "Interpolated Position Mode"; break;
    //            default: m_strActiveMode = "Unknown Mode";
    //        }
    //    }
    //    else
    //    {
    //        StopTimer();
    //        ShowErrorInformation(m_ulErrorCode);

    //        m_strActiveMode = "Unknown Mode";
    //    }
    //}
    //else
    //{
    //    m_strActiveMode = "Unknown Mode";
    //}

    //if(oResult)
    //{
    //    oResult = VCS_GetEnableState(m_KeyHandle, m_usNodeId, &oEnable, &m_ulErrorCode);

    //    if(oResult)
    //    {
    //        m_DeviceSettings.EnableWindow(!oEnable);
    //        m_Enable.EnableWindow(!oEnable);
    //        m_Disable.EnableWindow(oEnable);
    //        m_Move.EnableWindow(oEnable);
    //        m_Halt.EnableWindow(oEnable);
    //    }
    //    else
    //    {
    //        StopTimer();
    //        ShowErrorInformation(m_ulErrorCode);

    //        m_DeviceSettings.EnableWindow(oEnable);
    //        m_Enable.EnableWindow(oEnable);
    //        m_Disable.EnableWindow(!oEnable);
    //        m_Move.EnableWindow(!oEnable);
    //        m_Halt.EnableWindow(!oEnable);
    //    }
    //}
    //else
    //{
    //    m_DeviceSettings.EnableWindow(oEnable);
    //    m_Enable.EnableWindow(!oEnable);
    //    m_Disable.EnableWindow(!oEnable);
    //    m_Move.EnableWindow(!oEnable);
    //    m_Halt.EnableWindow(!oEnable);
    //}

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
    }
    else
    {
        m_lActualValue = 0;
        m_lStartPosition = 0;
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