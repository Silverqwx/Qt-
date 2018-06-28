#ifndef MYLABEL
#define MYLABEL

#include <QLabel>
#include <QWheelEvent>
#include <QMouseEvent>
#include "ScaleImage.h"
#include "QWX_Optimized_Position_Orientation.h"

class QWX_myLabel :public QLabel
{
	Q_OBJECT
public:
	explicit QWX_myLabel(QLabel *label, QWidget *parent = 0);
	~QWX_myLabel();
private:
	//QImage *image;//QImageͼ��
	QWX_ScaleImage scale_image;//ͼ��߶ȱ任���������ʵ��ͼ��ĳ߶ȱ任�����ţ�
	QLabel *coordinate_label;//��ʾ����ı�ǩ�ؼ�ָ�룬��ui�е�label_2ָ����ͬ
	void mousePressEvent(QMouseEvent* event);//����������ۺ���
	void wheelEvent(QWheelEvent *event);//���ع��ֲۺ���
	void mouseMoveEvent(QMouseEvent* event);//��������ƶ��ۺ���
	void load_image();

private slots:
	void load_rgb_image_Event();//����ͼ��ۺ���
	void load_gray_image_Event();

public slots:
	//void Coordinate_Update_Event(QMouseEvent* event, QLabel *label);
};

#endif // !MYLABEL

