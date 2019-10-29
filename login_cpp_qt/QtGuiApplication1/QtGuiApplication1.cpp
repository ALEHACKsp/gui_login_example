#include "QtGuiApplication1.h"
#include <string>

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//ui.txt_usr->setText("0");

	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(login()));
}


void QtGuiApplication1::exit() {
	QApplication::exit();
}

void QtGuiApplication1::login() {
	std::string lgn = (ui.txt_usr->text()).toStdString();
	std::string pwd = (ui.txt_pwd->text()).toStdString();
	ui.label_3->setText("loading...");
}

