#ifndef SCALEIMAGE
#define SCALEIMAGE

#include <opencv2/opencv.hpp>

using namespace cv;

class QWX_ScaleImage
{
public:
	Mat image;//���������ԭͼ��
	Mat resized;//����߶ȱ任���ͼ��
	//������һ�ε��и�������Ϣ
	//Ox��OyΪ��ԭͼ������ϵ�е����Ͻ�����
	//width��heightΪ�и�����Ŀ�͸�
	int Ox, Oy, width, height;
	double k;//���ŵı���ϵ������ʾ���ź��ͼ��Ϊԭͼ��Ķ��ٱ�
	QWX_ScaleImage();
	void init_resize_first();//�����ź��иʽ�ĳ�ʼ������
	void init_cut_first();//���и�����ŷ�ʽ�ĳ�ʼ������
	//�����ź��иʽ�ĳ߶ȱ任�����ţ�����
	//_position_kx��_position_ky�������λ���ڱ�ǩ�е����λ�ã�������ϵ��,Ϊ����ֵ����ߵı�ֵ
	//_scale_kΪ�˴����ű���ϵ��
	//_src�������ر任��ͼ��
	bool scale_resize_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src);
	//���и�����ŷ�ʽ�ĳ߶ȱ任�����ţ�����
	//_position_kx��_position_ky�������λ���ڱ�ǩ�е����λ�ã�������ϵ��,Ϊ����ֵ����ߵı�ֵ
	//_scale_kΪ�˴����ű���ϵ��
	//_src�������ر任��ͼ��
	bool scale_cut_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src);
};

#endif // !SCALEIMAGE
