#include "myLabel.h"

myLabel::myLabel(QLabel *label, QWidget *parent) :coordinate_label(label), QLabel(parent)
{
	setText("init");
	image = new QImage;
	//cvimg = cv::Mat();
	k = 1.0;
}

void myLabel::mousePressEvent(QMouseEvent* event)
{
	setText("clicked");
}

//void myLabel::wheelEvent(QWheelEvent *event)
//{
//	setText("wheel");
//}

void myLabel::wheelEvent(QWheelEvent *event)
{
	/*QPoint point = event->pos();
	setText(QString::number(point.x()));*/
	Mat scaled;
	bool err = true;
	QPoint point = event->pos();
	double kx = point.x() / 400.0,
		ky = point.y() / 400.0;
	if (event->delta() > 0)
	{		
		err = scale_image.scale_cut_first(kx, ky, 1.2, scaled);
	}
	else
	{
		err = scale_image.scale_cut_first(kx, ky, 0.8, scaled);
	}
	if (!err) return;
	//QImage *temp = new QImage;
	//*temp = image->scaled(image->width() * k, image->height() * k, Qt::KeepAspectRatio);
	uchar *pcv = (uchar*)scaled.data;
	QImage temp(pcv, 400, 400, scaled.step, QImage::Format_RGB888);
	setPixmap(QPixmap::fromImage(temp));
}

void myLabel::load_image_Event()
{
	/*scale_image.image = imread("zoro.jpg");
	cvtColor(scale_image.image, scale_image.image, CV_BGR2RGB);
	scale_image.Ox = (scale_image.image.cols - 400) / 2;
	scale_image.Oy = (scale_image.image.rows - 400) / 2;
	scale_image.k = 1.0;*/
	scale_image.init_cut_first();
	//cv::resize(scale_image.image,)
	uchar *pcv = (uchar*)scale_image.resized.data;
	QImage temp(pcv, scale_image.resized.cols, scale_image.resized.rows, scale_image.resized.step, QImage::Format_RGB888);
	setPixmap(QPixmap::fromImage(temp));
	setAlignment(Qt::AlignLeft);
}

void myLabel::mouseMoveEvent(QMouseEvent* event)
{
	QPoint ppos;
	ppos = event->pos();
	QString str = QString::number(ppos.x(), 10) + "," + QString::number(ppos.y(), 10);
	coordinate_label->setText(str);
}

//void myLabel::Coordinate_Update_Event(QMouseEvent* event, QLabel *label)
//{
//	QPoint ppos;
//	//ppos = event->globalPos();
//	ppos = event->pos();
//	QString str = QString::number(ppos.x(), 10) + "," + QString::number(ppos.y(), 10);
//	label->setText(str);
//}
