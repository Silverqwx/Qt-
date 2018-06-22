#include "myQt.h"

myQt::myQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	ui.centralWidget->setMouseTracking(true);	
	setMouseTracking(true);
	//ui.gridLayoutWidget->setMouseTracking(true);
	ui.label->setMouseTracking(true);
	image = new QImage;
	k = 1.0;
}

void myQt::Button_ok_clicked()
{
	//int i = 789;
	ui.label->setText("123");
}

void myQt::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0)
	{
		k *= 2;
	}
	else
	{
		k /= 2;
	}
	QImage *temp = new QImage;
	*temp = image->scaled(image->width() * k, image->height() * k, Qt::KeepAspectRatio);
	ui.label->setPixmap(QPixmap::fromImage(*temp));
}

void myQt::load_image_Event()
{
	QString filename = "zoro.jpg";
	
	if (!image->load(filename))
	{
		ui.label->setText("load image failed!!!");
		return;
	}
	ui.label->setPixmap(QPixmap::fromImage(*image));
}

void myQt::mouseMoveEvent(QMouseEvent* event)
{
	QPoint ppos;
	//ppos = event->globalPos();
	ppos = event->pos();
	QString str = QString::number(ppos.x(), 10) + "," + QString::number(ppos.y(), 10);
	ui.label_2->setText(str);
}