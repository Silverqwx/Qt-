#include "myQt.h"

myQt::myQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void myQt::Button_ok_clicked()
{
	ui.label->setText("123");
}

void myQt::wheelEvent(QWheelEvent *event)
{
	ui.label->setText("111");
}