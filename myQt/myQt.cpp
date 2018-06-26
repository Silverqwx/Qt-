#include "myQt.h"

myQt::myQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	
	mylabel = new myLabel(ui.label_2, this);
	mylabel->setObjectName(QStringLiteral("label"));
	mylabel->setGeometry(QRect(20, 20, 400, 400));
	ui.centralWidget->setMouseTracking(true);
	setMouseTracking(true);
	mylabel->setMouseTracking(true);

	connect(this->ui.load_image, SIGNAL(clicked()), this->mylabel, SLOT(load_image_Event()));
	//connect(this, SIGNAL(Coordinate_Update(QMouseEvent *, QLabel *)), this->mylabel, SLOT(Coordinate_Update_Event(QMouseEvent* , QLabel *)));
}

void myQt::Button_ok_clicked()
{
	//int i = 789;
	//ui.label->setText("123");
	mylabel->setText("123");
}

