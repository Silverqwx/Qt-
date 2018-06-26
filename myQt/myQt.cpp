#include "myQt.h"

QWX_myQt::QWX_myQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	//��ǩ�����ʼ��
	mylabel = new QWX_myLabel(ui.label_2, this);
	mylabel->setObjectName(QStringLiteral("label"));
	mylabel->setGeometry(QRect(20, 20, 400, 400));
	//�����׷�٣��Ա�ʵʱ��ʾ������Ϣ
	ui.centralWidget->setMouseTracking(true);
	setMouseTracking(true);
	mylabel->setMouseTracking(true);
	//���Ӽ���ͼ��ť�ĵ���źźͱ�ǩ����ļ���ͼ���
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

