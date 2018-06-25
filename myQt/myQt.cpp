#include "myQt.h"

myQt::myQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	
	mylabel = new myLabel(ui.label_2, this);
	mylabel->setObjectName(QStringLiteral("label"));
	mylabel->setGeometry(QRect(20, 20, 400, 400));
	ui.centralWidget->setMouseTracking(true);
	setMouseTracking(true);
	//ui.gridLayoutWidget->setMouseTracking(true);
	//ui.label->setMouseTracking(true);
	mylabel->setMouseTracking(true);

	connect(this->ui.load_image, SIGNAL(clicked()), this->mylabel, SLOT(load_image_Event()));
	//connect(this, SIGNAL(Coordinate_Update(QMouseEvent *, QLabel *)), this->mylabel, SLOT(Coordinate_Update_Event(QMouseEvent* , QLabel *)));
}

void myQt::Button_ok_clicked()
{
	//int i = 789;
	//ui.label->setText("123");
	mylabel->setText("123");
}

//void myQt::wheelEvent(QWheelEvent *event)
//{
//	if (event->delta() > 0)
//	{
//		k *= 2;
//	}
//	else
//	{
//		k /= 2;
//	}
//	QImage *temp = new QImage;
//	*temp = image->scaled(image->width() * k, image->height() * k, Qt::KeepAspectRatio);
//	//ui.label->setPixmap(QPixmap::fromImage(*temp));
//}

//void myQt::load_image_Event()
//{
//	QString filename = "zoro.jpg";
//	
//	if (!image->load(filename))
//	{
//		mylabel->setText("load image failed!!!");
//		return;
//	}
//	//ui.label->setPixmap(QPixmap::fromImage(*image));
//	mylabel->setPixmap(QPixmap::fromImage(*image));
//}

//void myQt::mouseMoveEvent(QMouseEvent* event)
//{
//	emit Coordinate_Update(event, ui.label_2);
//}

void enterEvent(QEvent * event)
{

}

//void myQt::pushbuttonEvent()
//{
//	ui.label_3->setText("pushbutton");
//}