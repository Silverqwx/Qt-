#ifndef MYLABEL
#define MYLABEL

#include <QLabel>
#include <QWheelEvent>
#include <QMouseEvent>
#include "ScaleImage.h"

class myLabel :public QLabel
{
	Q_OBJECT
public:
	explicit myLabel(QLabel *label,QWidget *parent = 0);
	~myLabel(){}
private:
	double k;
	QImage *image;
	ScaleImage scale_image;
	QLabel *coordinate_label;
	void mousePressEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent *event);
	void mouseMoveEvent(QMouseEvent* event);

private slots:
	void load_image_Event();

public slots:
	//void Coordinate_Update_Event(QMouseEvent* event, QLabel *label);
};

#endif // !MYLABEL

