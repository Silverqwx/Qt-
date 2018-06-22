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

void myQt::load_image_Event()
{
	QString filename = "zoro.jpg";
	QImage *image = new QImage;
	if (!image->load(filename))
	{
		ui.label->setText("load image failed!!!");
		return;
	}
	ui.label->setPixmap(QPixmap::fromImage(*image));
}