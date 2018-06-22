#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_myQt.h"

class myQt : public QMainWindow
{
	Q_OBJECT

public:
	myQt(QWidget *parent = Q_NULLPTR);

private:
	Ui::myQtClass ui;

signals:
	void wheelsignal(QWheelEvent *event);

private slots:
	void Button_ok_clicked();
	void wheelEvent(QWheelEvent *event);
	void load_image_Event();
};