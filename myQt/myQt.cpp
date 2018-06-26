#include "myQt.h"

QWX_myQt::QWX_myQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	//标签对象初始化
	mylabel = new QWX_myLabel(ui.label_2, this);
	mylabel->setObjectName(QStringLiteral("label"));
	mylabel->setGeometry(QRect(20, 20, 400, 400));
	//打开鼠标追踪，以便实时显示坐标信息
	ui.centralWidget->setMouseTracking(true);
	setMouseTracking(true);
	mylabel->setMouseTracking(true);
	//连接加载图像按钮的点击信号和标签对象的加载图像槽
	connect(this->ui.load_image, SIGNAL(clicked()), this->mylabel, SLOT(load_image_Event()));
	//connect(this, SIGNAL(Coordinate_Update(QMouseEvent *, QLabel *)), this->mylabel, SLOT(Coordinate_Update_Event(QMouseEvent* , QLabel *)));
}

QWX_myQt::~QWX_myQt()
{
	delete mylabel;
}

void QWX_myQt::Button_ok_clicked()
{
	//int i = 789;
	//ui.label->setText("123");
	mylabel->setText("123");
}

