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
	QWX_myLabel *mylabel;//��ǩ����
	QWX_myResultLabel *result_label;//������ʾ���ֽ��

private slots:
	void Button_ok_clicked();//��ťok�Ĳ�
};
