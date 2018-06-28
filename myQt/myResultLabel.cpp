#include "myResultLabel.h"

QWX_myResultLabel::QWX_myResultLabel(QLabel *_label, QWidget *_parent) :coordinate_label(_label), QLabel(_parent)
{
	setText("init");
	//image = new QImage;
}

QWX_myResultLabel::~QWX_myResultLabel()
{
	//delete image;
}

void QWX_myResultLabel::mousePressEvent(QMouseEvent* event)
{
	setText("clicked");
}

//void myLabel::wheelEvent(QWheelEvent *event)
//{
//	setText("wheel");
//}

void QWX_myResultLabel::wheelEvent(QWheelEvent *event)
{
	Mat scaled;//Mat����׼����ų߶ȱ任�����ͼ��,������ʾ
	bool err = true;//��־λ���ж������Ƿ����
	QPoint point = event->pos();//��ȡ���λ���ڱ�ǩ�ռ�����ϵ�е�����
	double kx = point.x() / 400.0,
		ky = point.y() / 400.0;//������굱ǰλ���ڱ�ǩ�еı�����ϵ�����λ�ã�
	if (event->delta() > 0)
	{		
		err = scale_image.scale_cut_first(kx, ky, 1.2, scaled);//�������Ϲ����Ŵ�ϵ��1.2,
	}
	else
	{
		err = scale_image.scale_cut_first(kx, ky, 0.8, scaled);//�������¹�����С��ϵ��0.8
	}
	if (!err) return;//����������أ������˴��¼�
	//��Mat������QImage����������ʾ
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

void QWX_myResultLabel::load_image()
{
	String filename = "eye.jpg";
	scale_image.init_cut_first(filename);//��ʼ��
	//��Mat������QImage����������ʾ
	/*uchar *pcv = (uchar*)scale_image.resized.data;
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
	}*/
	QImage temp = scale_image.QWX_Mat2QImage(scale_image.resized);
	
	setPixmap(QPixmap::fromImage(temp));
	setAlignment(Qt::AlignLeft);//��ʾ��ʽΪ���϶���
}

void QWX_myResultLabel::load_rgb_image_Event()
{
	scale_image.type = RGB;
	load_image();
}

void QWX_myResultLabel::load_gray_image_Event()
{
	scale_image.type = Gray;
	load_image();
}

void QWX_myResultLabel::mouseMoveEvent(QMouseEvent* event)
{
	//��ȡ����ڱ�ǩ����ϵ�е�����λ�ò���ʾ
	QPoint ppos = event->pos();
	double kx = ppos.x() / 400.0,
		ky = ppos.y() / 400.0;//������굱ǰλ���ڱ�ǩ�еı�����ϵ�����λ�ã�
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
