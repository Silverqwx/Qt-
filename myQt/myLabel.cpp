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
	QImage temp(pcv, 400, 400, scaled.step, QImage::Format_RGB888);
	setPixmap(QPixmap::fromImage(temp));
}

void QWX_myLabel::load_image_Event()
{
	scale_image.init_cut_first();//��ʼ��
	//��Mat������QImage����������ʾ
	uchar *pcv = (uchar*)scale_image.resized.data;
	QImage temp(pcv, scale_image.resized.cols, scale_image.resized.rows, scale_image.resized.step, QImage::Format_RGB888);
	setPixmap(QPixmap::fromImage(temp));
	setAlignment(Qt::AlignLeft);//��ʾ��ʽΪ���϶���
}

void QWX_myLabel::mouseMoveEvent(QMouseEvent* event)
{
	//��ȡ����ڱ�ǩ����ϵ�е�����λ�ò���ʾ
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
