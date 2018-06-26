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
	QImage temp(pcv, 400, 400, scaled.step, QImage::Format_RGB888);
	setPixmap(QPixmap::fromImage(temp));
}

void QWX_myLabel::load_image_Event()
{
	scale_image.init_cut_first();//初始化
	//用Mat对象构造QImage对象，用于显示
	uchar *pcv = (uchar*)scale_image.resized.data;
	QImage temp(pcv, scale_image.resized.cols, scale_image.resized.rows, scale_image.resized.step, QImage::Format_RGB888);
	setPixmap(QPixmap::fromImage(temp));
	setAlignment(Qt::AlignLeft);//显示方式为左上对齐
}

void QWX_myLabel::mouseMoveEvent(QMouseEvent* event)
{
	//获取鼠标在标签坐标系中的坐标位置并显示
	QPoint ppos = event->pos();
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
