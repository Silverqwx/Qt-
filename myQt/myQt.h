#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_myQt.h"
//#include <QWheelEvent>
#include "myLabel.h"

class QWX_myQt : public QMainWindow
{
	Q_OBJECT

public:
	QWX_myQt(QWidget *parent = Q_NULLPTR);
	~QWX_myQt();

private:
	Ui::myQtClass ui;
	QWX_myLabel *mylabel;//标签对象
	QWX_myResultLabel *result_label;//用来显示各种结果

private slots:
	void Button_ok_clicked();//按钮ok的槽
};
