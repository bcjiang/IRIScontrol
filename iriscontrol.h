#ifndef IRISCONTROL_H
#define IRISCONTROL_H

#include <QtGui/QMainWindow>
#include "ui_iriscontrol.h"
#include <windows.h>

class IRIScontrol : public QMainWindow
{
	Q_OBJECT

public:
	IRIScontrol(QWidget *parent = 0, Qt::WFlags flags = 0);
	~IRIScontrol();

private:
	Ui::IRIScontrolClass ui;

public slots:
	void doSomething();
};

#endif // IRISCONTROL_H
