#ifndef QWX_MYLABEL
#define QWX_MYLABEL

#include "myResultLabel.h"

class QWX_myLabel :public QWX_myResultLabel
{
public:
	QWX_myResultLabel *result_label;
	explicit QWX_myLabel(QLabel *_label, QWX_myResultLabel *_result_label, QWidget *_parent = 0);
	void mouseMoveEvent(QMouseEvent* event);//��������ƶ��ۺ���
};

#endif // !QWX_MYRESULTLABEL


