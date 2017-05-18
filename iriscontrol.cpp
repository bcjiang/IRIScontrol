#include "iriscontrol.h"
#include <math.h>

#include <iostream>
#include<fstream>
#include<cmath>

#define PI 3.14159265

double find_motor(double roll_test,double pitch_test, double datapoint[48][3]){

	double dist[48];
	int short_index = 0;
	int shorter_index = 0;
	int shortest_index = 0;
	double short_dist = 10000;
	double shorter_dist = 10000;
	double shortest_dist = 10000;
	for(int i = 0; i<48; i++){
		dist[i] = sqrt(abs(pow(roll_test - datapoint[i][0],2) + pow(pitch_test - datapoint[i][1],2)));
		if(dist[i] < shortest_dist){
			short_dist = shorter_dist;
			short_index = shorter_index;
			shorter_dist = shortest_dist;
			shorter_index = shortest_index;
			shortest_dist = dist[i];
			shortest_index = i;
		}
		else{
			if(dist[i] < shorter_dist){
				short_dist = shorter_dist;
				short_index = shorter_index;
				shorter_dist = dist[i];
				shorter_index = i;
			}
			else{
				if(dist[i] < short_dist){
					short_dist = dist[i];
					short_index = i;
				}
			}
		}
	}
	
    double x1,x2,x3,y1,y2,y3,mu,lambda,output_value;
	x1 = datapoint[shorter_index][0] - datapoint[shortest_index][0];
	x2 = datapoint[short_index][0] - datapoint[shortest_index][0];
	y1 = datapoint[shorter_index][1] - datapoint[shortest_index][1];
	y2 = datapoint[short_index][1] - datapoint[shortest_index][1];
	x3 = roll_test - datapoint[shortest_index][0];
	y3 = pitch_test - datapoint[shortest_index][1];

	mu = (x2*y3 - x3*y2)/(x2*y1 - x1*y2);
	lambda = (x1*y3 - x3*y1)/(x1*y2 - x2*y1);
	
	output_value = datapoint[shortest_index][2] 
	               + mu * (datapoint[shorter_index][2] - datapoint[shortest_index][2])
				   + lambda * (datapoint[short_index][2] - datapoint[shortest_index][2]);
	
    return output_value;
}

IRIScontrol::IRIScontrol(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	, m_strNodeId(_T("1"))
	, m_oRadio(0)
	, m_lStartPosition(0)
	//, m_lStartPosition2(0)
	, m_lStartPosition3(0)
	, m_lStartPosition4(0)
	, m_lTargetPosition(2000)
	//, m_lTargetPosition2(2000)
	, m_lTargetPosition3(2000)
	, m_lTargetPosition4(2000)
	, m_lTargetPoseRoll(0)
	, m_lTargetPosePitch(0)
	, m_lGimbalJointPosition(0.0,0.0,0.0)
{
	ui.setupUi(this);
	connect(ui.pBtnEnable,SIGNAL(clicked()),this,SLOT(OnButtonEnable()));
	connect(ui.pBtnDisable,SIGNAL(clicked()),this,SLOT(OnButtonDisable()));
	connect(ui.pBtnEnableTeleop,SIGNAL(clicked()),this,SLOT(OnButtonEnableTeleop()));
	connect(ui.eTargetPosition,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetPositionText(QString)));
	//connect(ui.eTargetPosition2,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetPositionText2(QString)));
	connect(ui.eTargetPosition3,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetPositionText3(QString)));
	connect(ui.eTargetPosition4,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetPositionText4(QString)));
	connect(ui.eTargetRoll,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetRollText(QString)));
	connect(ui.eTargetPitch,SIGNAL(textChanged(QString)),this,SLOT(UpdateTargetPitchText(QString)));
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
	///////////////////////////////
	// This part reads the mapping data
	int x,y;
	std::ifstream in("motor1.txt");
	for(x=0;x<48;x++){
		for(y=0;y<3;y++){
			in>>datapoint1[x][y];
			//cout<<datapoint[x][y];
		}
	}
	in.close();

	std::ifstream in2("motor3.txt");
	for(x=0;x<48;x++){
		for(y=0;y<3;y++){
			in2>>datapoint3[x][y];
		}
	}
	in2.close();

	std::ifstream in3("motor41.txt");
	for(x=0;x<48;x++){
		for(y=0;y<3;y++){
			in3>>datapoint41[x][y];
		}
	}
	in3.close();

	std::ifstream in4("motor43.txt");
	for(x=0;x<48;x++){
		for(y=0;y<3;y++){
			in4>>datapoint43[x][y];
		}
	}
	in4.close();
    //////////////////////////////////////////////////////
	m_oImmediately = TRUE;
	m_oUpdateActive = FALSE;
	m_oTeleopActive = FALSE;
	m_usNodeId = 1;
	//m_usNodeId2 = 2;
	m_usNodeId3 = 3;
	m_usNodeId4 = 4;

	HANDLE hNewKeyHandle;

	hNewKeyHandle = VCS_OpenDeviceDlg(&m_ulErrorCode);
	if(hNewKeyHandle)
	{
		m_KeyHandle = hNewKeyHandle;

		//Clear Error History
		if(VCS_ClearFault(m_KeyHandle, m_usNodeId, &m_ulErrorCode)
			//&& VCS_ClearFault(m_KeyHandle, m_usNodeId2, &m_ulErrorCode)
			&& VCS_ClearFault(m_KeyHandle, m_usNodeId3, &m_ulErrorCode)
			&& VCS_ClearFault(m_KeyHandle, m_usNodeId4, &m_ulErrorCode))
		{
			//Read Operation Mode
			if(VCS_GetOperationMode(m_KeyHandle, m_usNodeId, &m_bMode, &m_ulErrorCode)
				//&& VCS_GetOperationMode(m_KeyHandle, m_usNodeId2, &m_bMode, &m_ulErrorCode)
				&& VCS_GetOperationMode(m_KeyHandle, m_usNodeId3, &m_bMode, &m_ulErrorCode)
				&& VCS_GetOperationMode(m_KeyHandle, m_usNodeId4, &m_bMode, &m_ulErrorCode))
			{
				//Read Position Profile Objects
				if(VCS_GetPositionProfile(m_KeyHandle, m_usNodeId, &m_ulProfileVelocity, &m_ulProfileAcceleration, &m_ulProfileDeceleration, &m_ulErrorCode)
					//&& VCS_GetPositionProfile(m_KeyHandle, m_usNodeId2, &m_ulProfileVelocity, &m_ulProfileAcceleration, &m_ulProfileDeceleration, &m_ulErrorCode)
					&& VCS_GetPositionProfile(m_KeyHandle, m_usNodeId3, &m_ulProfileVelocity, &m_ulProfileAcceleration, &m_ulProfileDeceleration, &m_ulErrorCode)
					&& VCS_GetPositionProfile(m_KeyHandle, m_usNodeId4, &m_ulProfileVelocity, &m_ulProfileAcceleration, &m_ulProfileDeceleration, &m_ulErrorCode))
				{
					//Write Profile Position Mode
					if(VCS_SetOperationMode(m_KeyHandle, m_usNodeId, OMD_PROFILE_POSITION_MODE, &m_ulErrorCode)
						//&& VCS_SetOperationMode(m_KeyHandle, m_usNodeId2, OMD_PROFILE_POSITION_MODE, &m_ulErrorCode)
						&& VCS_SetOperationMode(m_KeyHandle, m_usNodeId3, OMD_PROFILE_POSITION_MODE, &m_ulErrorCode)
						&& VCS_SetOperationMode(m_KeyHandle, m_usNodeId4, OMD_PROFILE_POSITION_MODE, &m_ulErrorCode))
					{
						//Write Profile Position Objects
						if(VCS_SetPositionProfile(m_KeyHandle, m_usNodeId, 5000, 10000, 10000, &m_ulErrorCode)
							//&& VCS_SetPositionProfile(m_KeyHandle, m_usNodeId2, 5000, 10000, 10000, &m_ulErrorCode)
							&& VCS_SetPositionProfile(m_KeyHandle, m_usNodeId3, 5000, 10000, 10000, &m_ulErrorCode)
							&& VCS_SetPositionProfile(m_KeyHandle, m_usNodeId4, 5000, 10000, 10000, &m_ulErrorCode))
						{
							//Read Actual Position
							if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId, &m_lStartPosition, &m_ulErrorCode)
								//&& VCS_GetPositionIs(m_KeyHandle, m_usNodeId2, &m_lStartPosition2, &m_ulErrorCode)
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
		//|| !VCS_GetFaultState(m_KeyHandle, m_usNodeId2, &oFault, &m_ulErrorCode)
		|| !VCS_GetFaultState(m_KeyHandle, m_usNodeId3, &oFault, &m_ulErrorCode)
		|| !VCS_GetFaultState(m_KeyHandle, m_usNodeId4, &oFault, &m_ulErrorCode))
    {
        ShowErrorInformation(m_ulErrorCode);
        return;
    }

    if(oFault)
    {
        if(!VCS_ClearFault(m_KeyHandle, m_usNodeId, &m_ulErrorCode)
			//|| !VCS_ClearFault(m_KeyHandle, m_usNodeId2, &m_ulErrorCode)
			|| !VCS_ClearFault(m_KeyHandle, m_usNodeId3, &m_ulErrorCode)
			|| !VCS_ClearFault(m_KeyHandle, m_usNodeId4, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
            return;
        }
    }

    if(!VCS_SetEnableState(m_KeyHandle, m_usNodeId, &m_ulErrorCode)
		//|| !VCS_SetEnableState(m_KeyHandle, m_usNodeId2, &m_ulErrorCode)
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
		//|| !VCS_SetDisableState(m_KeyHandle, m_usNodeId2, &m_ulErrorCode)
		|| !VCS_SetDisableState(m_KeyHandle, m_usNodeId3, &m_ulErrorCode)
		|| !VCS_SetDisableState(m_KeyHandle, m_usNodeId4, &m_ulErrorCode))
    {
        ShowErrorInformation(m_ulErrorCode);
    }

	MessageBox(NULL,(LPCWSTR)L"Controllers disabled!",(LPCWSTR)L"System Message",MB_OK);
	ui.pBtnDisable->setEnabled(FALSE);
	timer->stop();
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
	UpdateStatus();
    UpdateNodeIdString();

    if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId, &m_lStartPosition, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId, m_lTargetPosition, m_oRadio, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }

	/*if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId2, &m_lStartPosition2, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId2, m_lTargetPosition2, m_oRadio, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }*/

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

	 //This part convert target pose into target motor rotation angles (qc) for roll angle
	if(m_lTargetPoseRoll > 20){m_lTargetPoseRoll = 20;}
	if(m_lTargetPoseRoll < 0){m_lTargetPoseRoll = 0;}
	if(m_lTargetPosePitch > 20){m_lTargetPosePitch = 20;}
	if(m_lTargetPosePitch < -20){m_lTargetPosePitch = -20;}

	if(m_lTargetPosePitch > 0){
		m_lTargetPosition = 45.94 - 1205 * m_lTargetPoseRoll + 29510 * m_lTargetPosePitch
			+423.2 * pow((double)m_lTargetPoseRoll,2) +789.2 * m_lTargetPoseRoll * m_lTargetPosePitch
			-3956 * pow((double)m_lTargetPosePitch,2) -39.96 * pow((double)m_lTargetPoseRoll,3)
			-29.35 * pow((double)m_lTargetPoseRoll,2) * m_lTargetPosePitch
			-82.98 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
			+237.9 * pow((double)m_lTargetPosePitch,3) +1.104 * pow((double)m_lTargetPoseRoll,4)
			+0.263 * pow((double)m_lTargetPoseRoll,3) * (double)m_lTargetPosePitch
			+2.032 * pow((double)m_lTargetPoseRoll,2) * pow((double)m_lTargetPosePitch,2)
			+2.594 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,3)
			-4.965 * pow((double)m_lTargetPosePitch,4);
		m_lTargetPosition4 = 396.2 + 8408*(double)m_lTargetPoseRoll +88.57 * (double)m_lTargetPosePitch
			-541.7 * pow((double)m_lTargetPoseRoll,2) -7.817 * (double)m_lTargetPoseRoll * (double)m_lTargetPosePitch
			-13.93 * pow((double)m_lTargetPosePitch,2) + 15.35 * pow((double)m_lTargetPoseRoll,3)
			-0.09291 * pow((double)m_lTargetPoseRoll,2)*(double)m_lTargetPosePitch
			+ 0.8539 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
			+ 0.5046 * pow((double)m_lTargetPosePitch,3);
		//m_lTargetPosition = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint1);
		//m_lTargetPosition4 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint41);
		m_lTargetPosition3 = 0;}

	else if(m_lTargetPosePitch < 0) {
		m_lTargetPosition3 = -1306 +1668 * m_lTargetPoseRoll -7596 * m_lTargetPosePitch
			-358.1 * pow((double)m_lTargetPoseRoll,2) -1090 * m_lTargetPoseRoll * m_lTargetPosePitch
			-446.4 * pow((double)m_lTargetPosePitch,2) +26.27 * pow((double)m_lTargetPoseRoll,3)
			+30.09 * pow((double)m_lTargetPoseRoll,2) * m_lTargetPosePitch
			-113.7 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
			-28.73 * pow((double)m_lTargetPosePitch,3) -0.6162 * pow((double)m_lTargetPoseRoll,4)
			-0.3839 * pow((double)m_lTargetPoseRoll,3) * (double)m_lTargetPosePitch
			+1.882 * pow((double)m_lTargetPoseRoll,2) * pow((double)m_lTargetPosePitch,2)
			-3.003 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,3)
			-0.7248 * pow((double)m_lTargetPosePitch,4);
		m_lTargetPosition4 = 790.8 + 7703*(double)m_lTargetPoseRoll + 197.2 * (double)m_lTargetPosePitch
			-420.3 * pow((double)m_lTargetPoseRoll,2) -6.029 * (double)m_lTargetPoseRoll * (double)m_lTargetPosePitch
			+33.78 * pow((double)m_lTargetPosePitch,2) +11.06 * pow((double)m_lTargetPoseRoll,3)
			-0.0784 * pow((double)m_lTargetPoseRoll,2)*(double)m_lTargetPosePitch
			-0.9495 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
			+1.228 * pow((double)m_lTargetPosePitch,3);
		//m_lTargetPosition3 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint3);
		//m_lTargetPosition4 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint43);
		m_lTargetPosition = 0;}
	else if(m_lTargetPosePitch == 0 && m_lTargetPoseRoll != 0) {
		m_lTargetPosition3 = 0;
		m_lTargetPosition4 = 790.8 + 7703*(double)m_lTargetPoseRoll + 197.2 * (double)m_lTargetPosePitch
			-420.3 * pow((double)m_lTargetPoseRoll,2) -6.029 * (double)m_lTargetPoseRoll * (double)m_lTargetPosePitch
			+33.78 * pow((double)m_lTargetPosePitch,2) +11.06 * pow((double)m_lTargetPoseRoll,3)
			-0.0784 * pow((double)m_lTargetPoseRoll,2)*(double)m_lTargetPosePitch
			-0.9495 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
			+1.228 * pow((double)m_lTargetPosePitch,3);
		//m_lTargetPosition3 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint3);
		//m_lTargetPosition4 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint43);
		m_lTargetPosition = 0;}
	else
	{
		m_lTargetPosition = 0;
		m_lTargetPosition3 = 0;
		m_lTargetPosition4 = 0;
	}

	if(m_lTargetPosition > 119000){m_lTargetPosition = 119000;}
	if(m_lTargetPosition < 0){m_lTargetPosition = 0;}
	if(m_lTargetPosition3 > 87000){m_lTargetPosition3 = 87000;}
	if(m_lTargetPosition3 <0){m_lTargetPosition3 = 0;}
	if(m_lTargetPosition4 > 74000){m_lTargetPosition4 = 74000;}
	if(m_lTargetPosition4 <0){m_lTargetPosition4 = 0;}

	//-----------------------------------------------------------------

    if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId, &m_lStartPosition, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId, m_lTargetPosition, 1, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }

	if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId3, &m_lStartPosition3, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId3, m_lTargetPosition3, 1, m_oImmediately, &m_ulErrorCode))
        {
            ShowErrorInformation(m_ulErrorCode);
        }
    }

	if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId4, &m_lStartPosition4, &m_ulErrorCode))
    {
        if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId4, m_lTargetPosition4, 1, m_oImmediately, &m_ulErrorCode))
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
		/*oResult = VCS_GetPositionIs(m_KeyHandle, m_usNodeId2, &m_lActualValue2, &m_ulErrorCode); 
		ui.eTruePosition2->setText(QString::number(m_lActualValue2));
        if(!oResult)
        {
			timer->stop();
            ShowErrorInformation(m_ulErrorCode);

            m_lActualValue2 = 0;
            m_lStartPosition2 = 0;
        }*/
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
			m_lTargetPosePitch = (m_lGimbalJointPosition[0] + 0.14) / 0.025;
			m_lTargetPoseRoll = (m_lGimbalJointPosition[1] + 0.22) / 0.016;
			if(m_lTargetPosePitch > 20){m_lTargetPosePitch = 20;}
			if(m_lTargetPosePitch < -20){m_lTargetPosePitch = -20;}
			if(m_lTargetPoseRoll > 20){m_lTargetPoseRoll = 20;}
			if(m_lTargetPoseRoll < 0){m_lTargetPoseRoll = 0;}
			ui.eMasterPosition->setText(QString::number(m_lTargetPosePitch));
			ui.eMasterPosition2->setText(QString::number(m_lTargetPoseRoll));


			//This part convert target pose into target motor rotation angles (qc) for roll angle

			if(m_lTargetPosePitch > 0){
				m_lTargetPosition = 45.94 - 1205 * m_lTargetPoseRoll + 29510 * m_lTargetPosePitch
					+423.2 * pow((double)m_lTargetPoseRoll,2) +789.2 * m_lTargetPoseRoll * m_lTargetPosePitch
					-3956 * pow((double)m_lTargetPosePitch,2) -39.96 * pow((double)m_lTargetPoseRoll,3)
					-29.35 * pow((double)m_lTargetPoseRoll,2) * m_lTargetPosePitch
					-82.98 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
					+237.9 * pow((double)m_lTargetPosePitch,3) +1.104 * pow((double)m_lTargetPoseRoll,4)
					+0.263 * pow((double)m_lTargetPoseRoll,3) * (double)m_lTargetPosePitch
					+2.032 * pow((double)m_lTargetPoseRoll,2) * pow((double)m_lTargetPosePitch,2)
					+2.594 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,3)
					-4.965 * pow((double)m_lTargetPosePitch,4);
				m_lTargetPosition4 = 396.2 + 8408*(double)m_lTargetPoseRoll +88.57 * (double)m_lTargetPosePitch
					-541.7 * pow((double)m_lTargetPoseRoll,2) -7.817 * (double)m_lTargetPoseRoll * (double)m_lTargetPosePitch
					-13.93 * pow((double)m_lTargetPosePitch,2) + 15.35 * pow((double)m_lTargetPoseRoll,3)
					-0.09291 * pow((double)m_lTargetPoseRoll,2)*(double)m_lTargetPosePitch
					+ 0.8539 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
					+ 0.5046 * pow((double)m_lTargetPosePitch,3);
				//m_lTargetPosition = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint1);
				//m_lTargetPosition4 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint41);
				m_lTargetPosition3 = 0;}

			else if(m_lTargetPosePitch < 0) {
				m_lTargetPosition3 = -1306 +1668 * m_lTargetPoseRoll -7596 * m_lTargetPosePitch
					-358.1 * pow((double)m_lTargetPoseRoll,2) -1090 * m_lTargetPoseRoll * m_lTargetPosePitch
					-446.4 * pow((double)m_lTargetPosePitch,2) +26.27 * pow((double)m_lTargetPoseRoll,3)
					+30.09 * pow((double)m_lTargetPoseRoll,2) * m_lTargetPosePitch
					-113.7 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
					-28.73 * pow((double)m_lTargetPosePitch,3) -0.6162 * pow((double)m_lTargetPoseRoll,4)
					-0.3839 * pow((double)m_lTargetPoseRoll,3) * (double)m_lTargetPosePitch
					+1.882 * pow((double)m_lTargetPoseRoll,2) * pow((double)m_lTargetPosePitch,2)
					-3.003 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,3)
					-0.7248 * pow((double)m_lTargetPosePitch,4);
				m_lTargetPosition4 = 790.8 + 7703*(double)m_lTargetPoseRoll + 197.2 * (double)m_lTargetPosePitch
					-420.3 * pow((double)m_lTargetPoseRoll,2) -6.029 * (double)m_lTargetPoseRoll * (double)m_lTargetPosePitch
					+33.78 * pow((double)m_lTargetPosePitch,2) +11.06 * pow((double)m_lTargetPoseRoll,3)
					-0.0784 * pow((double)m_lTargetPoseRoll,2)*(double)m_lTargetPosePitch
					-0.9495 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
					+1.228 * pow((double)m_lTargetPosePitch,3);
				//m_lTargetPosition3 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint3);
				//m_lTargetPosition4 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint43);
				m_lTargetPosition = 0;}
			else if(m_lTargetPosePitch == 0 && m_lTargetPoseRoll != 0) {
				m_lTargetPosition3 = 0;
				m_lTargetPosition4 = 790.8 + 7703*(double)m_lTargetPoseRoll + 197.2 * (double)m_lTargetPosePitch
					-420.3 * pow((double)m_lTargetPoseRoll,2) -6.029 * (double)m_lTargetPoseRoll * (double)m_lTargetPosePitch
					+33.78 * pow((double)m_lTargetPosePitch,2) +11.06 * pow((double)m_lTargetPoseRoll,3)
					-0.0784 * pow((double)m_lTargetPoseRoll,2)*(double)m_lTargetPosePitch
					-0.9495 * (double)m_lTargetPoseRoll * pow((double)m_lTargetPosePitch,2)
					+1.228 * pow((double)m_lTargetPosePitch,3);
				//m_lTargetPosition3 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint3);
				//m_lTargetPosition4 = find_motor(m_lTargetPoseRoll,m_lTargetPosePitch,datapoint43);
				m_lTargetPosition = 0;}
			else
			{
				m_lTargetPosition = 0;
				m_lTargetPosition3 = 0;
				m_lTargetPosition4 = 0;
			}

			if(m_lTargetPosition > 119000){m_lTargetPosition = 119000;}
			if(m_lTargetPosition < 0){m_lTargetPosition = 0;}
			if(m_lTargetPosition3 > 87000){m_lTargetPosition3 = 87000;}
			if(m_lTargetPosition3 <0){m_lTargetPosition3 = 0;}
			if(m_lTargetPosition4 > 74000){m_lTargetPosition4 = 74000;}
			if(m_lTargetPosition4 <0){m_lTargetPosition4 = 0;}

			//-----------------------------------------------------------------

			if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId, &m_lStartPosition, &m_ulErrorCode))
			{
				if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId, m_lTargetPosition, 1, m_oImmediately, &m_ulErrorCode))
				{
					ShowErrorInformation(m_ulErrorCode);
				}
			}

			if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId3, &m_lStartPosition3, &m_ulErrorCode))
			{
				if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId3, m_lTargetPosition3, 1, m_oImmediately, &m_ulErrorCode))
				{
					ShowErrorInformation(m_ulErrorCode);
				}
			}

			if(VCS_GetPositionIs(m_KeyHandle, m_usNodeId4, &m_lStartPosition4, &m_ulErrorCode))
			{
				if(!VCS_MoveToPosition(m_KeyHandle, m_usNodeId4, m_lTargetPosition4, 1, m_oImmediately, &m_ulErrorCode))
				{
					ShowErrorInformation(m_ulErrorCode);
				}
			}

		}
		else{
			//MessageBox(NULL,(LPCWSTR)L"Disabled teleoperation!",(LPCWSTR)L"System Message",MB_OK);
			ui.eMasterPosition->setText(QString::number(0));
			ui.eMasterPosition2->setText(QString::number(0));
		}
    }
    else
    {
        m_lActualValue = 0;
		//m_lActualValue2 = 0;
		m_lActualValue3 = 0;
		m_lActualValue4 = 0;
        m_lStartPosition = 0;
		//m_lStartPosition2 = 0;
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

//void IRIScontrol::UpdateTargetPositionText2(QString text)
//{
//	m_lTargetPosition2 = text.toLong();
//}

void IRIScontrol::UpdateTargetPositionText3(QString text)
{
	m_lTargetPosition3 = text.toLong();
}

void IRIScontrol::UpdateTargetPositionText4(QString text)
{
	m_lTargetPosition4 = text.toLong();
}


void IRIScontrol::UpdateTargetRollText(QString text)
{
	m_lTargetPoseRoll = text.toLong();
}

void IRIScontrol::UpdateTargetPitchText(QString text)
{
	m_lTargetPosePitch = text.toLong();
}