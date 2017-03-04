#include "iriscontrol.h"

IRIScontrol::IRIScontrol(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.testButton,SIGNAL(clicked()),this,SLOT(doSomething()));
}

IRIScontrol::~IRIScontrol()
{

}

void IRIScontrol::doSomething()
{
	MessageBox(NULL,(LPCWSTR)L"Test Message",(LPCWSTR)L"Test Message Window",MB_OK);
	//MessageBox::Show("Hello!");
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