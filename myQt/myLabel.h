#ifndef MYLABEL
#define MYLABEL

#include <QLabel>
#include <QWheelEvent>
#include <QMouseEvent>
#include "ScaleImage.h"

class QWX_myLabel :public QLabel
{
	Q_OBJECT
public:
	explicit QWX_myLabel(QLabel *label, QWidget *parent = 0);
	~QWX_myLabel();
private:
	//QImage *image;//QImage图像，
	QWX_ScaleImage scale_image;//图像尺度变换类对象，用来实现图像的尺度变换（缩放）
	QLabel *coordinate_label;//显示坐标的标签控件指针，和ui中的label_2指向相同
	void mousePressEvent(QMouseEvent* event);//重载鼠标点击槽函数
	void wheelEvent(QWheelEvent *event);//重载滚轮槽函数
	void mouseMoveEvent(QMouseEvent* event);//重载鼠标移动槽函数

private slots:
	void load_image_Event();//载入图像槽函数

public slots:
	//void Coordinate_Update_Event(QMouseEvent* event, QLabel *label);
};

#endif // !MYLABEL

