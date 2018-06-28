#include "myQt.h"

QWX_myQt::QWX_myQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	//��ǩ�����ʼ��
	result_label = new QWX_myResultLabel(ui.label_2, this);
	result_label->setObjectName(QStringLiteral("result_label"));
	result_label->setGeometry(QRect(500, 20, 360, 100));
	mylabel = new QWX_myLabel(ui.label_2, result_label, this);
	mylabel->setObjectName(QStringLiteral("label"));
	mylabel->setGeometry(QRect(20, 20, 400, 400));
	
	//�����׷�٣��Ա�ʵʱ��ʾ������Ϣ
	ui.centralWidget->setMouseTracking(true);
	setMouseTracking(true);
	mylabel->setMouseTracking(true);
	result_label->setMouseTracking(true);
	//���Ӽ���ͼ��ť�ĵ���źźͱ�ǩ����ļ���ͼ���
	connect(this->ui.load_rgb_image, SIGNAL(clicked()), this->mylabel, SLOT(load_rgb_image_Event()));
	connect(this->ui.load_gray_image, SIGNAL(clicked()), this->mylabel, SLOT(load_gray_image_Event()));
}

QWX_myQt::~QWX_myQt()
{
	delete mylabel;
	delete result_label;
}

void QWX_myQt::Button_ok_clicked()
{
	//int i = 789;
	//ui.label->setText("123");
	mylabel->setText("123");
}

