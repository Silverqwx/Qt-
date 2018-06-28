#include "myLabel.h"

QWX_myLabel::QWX_myLabel(QLabel *label, QWidget *parent) :coordinate_label(label), QLabel(parent)
{
	setText("init");
	//image = new QImage;
}

QWX_myLabel::~QWX_myLabel()
{
	//delete image;
}

void QWX_myLabel::mousePressEvent(QMouseEvent* event)
{
	setText("clicked");
}

//void myLabel::wheelEvent(QWheelEvent *event)
//{
//	setText("wheel");
//}

void QWX_myLabel::wheelEvent(QWheelEvent *event)
{
	Mat scaled;//Mat对象，准备存放尺度变换过后的图像,用于显示
	bool err = true;//标志位，判断缩放是否出错
	QPoint point = event->pos();//获取鼠标位置在标签空间坐标系中的坐标
	double kx = point.x() / 400.0,
		ky = point.y() / 400.0;//计算鼠标当前位置在标签中的比例关系（相对位置）
	if (event->delta() > 0)
	{		
		err = scale_image.scale_cut_first(kx, ky, 1.2, scaled);//滚轮往上滚，放大，系数1.2,
	}
	else
	{
		err = scale_image.scale_cut_first(kx, ky, 0.8, scaled);//滚轮向下滚，缩小，系数0.8
	}
	if (!err) return;//如果出错，返回，结束此次事件
	//用Mat对象构造QImage对象，用于显示
	uchar *pcv = (uchar*)scaled.data;
	QImage temp;
	switch (scale_image.type)
	{
	case Gray:
		temp = QImage(pcv, scale_image.resized.cols, scale_image.resized.rows, scale_image.resized.step, QImage::Format_Grayscale8);
		break;
	case RGB:
		temp = QImage(pcv, scale_image.resized.cols, scale_image.resized.rows, scale_image.resized.step, QImage::Format_RGB888);
		break;
	default:
		break;
	}
	setPixmap(QPixmap::fromImage(temp));
}

void QWX_myLabel::load_image()
{
	scale_image.init_cut_first();//初始化
	//用Mat对象构造QImage对象，用于显示
	uchar *pcv = (uchar*)scale_image.resized.data;
	QImage temp;
	switch (scale_image.type)
	{
	case Gray:
		temp = QImage(pcv, scale_image.resized.cols, scale_image.resized.rows, scale_image.resized.step, QImage::Format_Grayscale8);
		break;
	case RGB:
		temp = QImage(pcv, scale_image.resized.cols, scale_image.resized.rows, scale_image.resized.step, QImage::Format_RGB888);
		break;
	default:
		break;
	}
	
	setPixmap(QPixmap::fromImage(temp));
	setAlignment(Qt::AlignLeft);//显示方式为左上对齐
}

void QWX_myLabel::load_rgb_image_Event()
{
	scale_image.type = RGB;
	load_image();
}

void QWX_myLabel::load_gray_image_Event()
{
	scale_image.type = Gray;
	load_image();
}

void QWX_myLabel::mouseMoveEvent(QMouseEvent* event)
{
	//获取鼠标在标签坐标系中的坐标位置并显示
	QPoint ppos = event->pos();
	double kx = ppos.x() / 400.0,
		ky = ppos.y() / 400.0;//计算鼠标当前位置在标签中的比例关系（相对位置）
	Point position = scale_image.QWX_get_position(kx, ky);
	if (position.y < 0 || position.y >= scale_image.image.rows || position.x < 0 || position.x >= scale_image.image.cols)
	{
		QString error_str = "out of the image!!!";
		coordinate_label->setText(error_str);
		return;
	}
	QString str = QString::number(position.y, 10) + "," + QString::number(position.x, 10) + "; ";
	switch (scale_image.type)
	{
	case Gray:
		str += QString::number(scale_image.image.at<uchar>(position.y, position.x), 10) + "; ";
		break;
	case RGB:
		str += QString::number(scale_image.image.at<Vec3b>(position.y, position.x)[0], 10) + ",";
		str += QString::number(scale_image.image.at<Vec3b>(position.y, position.x)[1], 10) + ",";
		str += QString::number(scale_image.image.at<Vec3b>(position.y, position.x)[2], 10) + "; ";
		break;
	default:
		break;
	}
	Mat kernel = Mat::eye(15, 15, CV_8UC1);
	QWX_Optimized_Position_Orientation opo;
	opo.QWX_init(kernel, 1, 20);
	float optimized_orientation = opo.QWX_compute(scale_image.image, position.y, position.x);
	str += QString::number(optimized_orientation);
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
