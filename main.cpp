#include "iriscontrol.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IRIScontrol w;
	w.show();
	w.OpenDevice();
	return a.exec();
}
