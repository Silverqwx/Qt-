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

private slots:
	void Button_ok_clicked();
};
