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
	MessageBox(NULL,(LPCWSTR)L"Test Message",(LPCWSTR)L"Test Message Window",MB_CANCELTRYCONTINUE);
}
