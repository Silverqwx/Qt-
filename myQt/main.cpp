#include "myQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	myQt w;
	w.show();
	return a.exec();
}
