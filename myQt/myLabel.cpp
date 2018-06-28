#include "myLabel.h"

QWX_myLabel::QWX_myLabel(QLabel *_label, QWX_myResultLabel *_result_label, QWidget *_parent) :QWX_myResultLabel(_label, _parent), result_label(_result_label)
{

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

	Mat fhist = opo.QWX_gethist(scale_image.image, position.y, position.x);
	QImage temp = scale_image.QWX_Mat2QImage(fhist);
	result_label->setPixmap(QPixmap::fromImage(temp));
}