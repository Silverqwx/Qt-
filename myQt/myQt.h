#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_myQt.h"
//#include <QWheelEvent>
#include "myLabel.h"

class myQt : public QMainWindow
{
	Q_OBJECT

public:
	myQt(QWidget *parent = Q_NULLPTR);

private:
	Ui::myQtClass ui;
	myLabel *mylabel;
	//QImage *image;
	//double k;

signals:
	//void wheelsignal(QWheelEvent *event);
	//void Coordinate_Update(QMouseEvent* event, QLabel *label);

private slots:
	void Button_ok_clicked();
	//void wheelEvent(QWheelEvent *event);
	//void load_image_Event();
	//void mouseMoveEvent(QMouseEvent* event);
	//void enterEvent(QEvent * event);
	//void pushbuttonEvent();
};
