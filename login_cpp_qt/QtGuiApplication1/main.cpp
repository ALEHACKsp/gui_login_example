#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>
#include <thread>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication1 w;
	w.show();
	return a.exec();
}
