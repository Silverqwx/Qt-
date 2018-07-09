#include "ScaleImage.h"

QWX_ScaleImage::QWX_ScaleImage() :Ox(0), Oy(0), width(400), height(400), k(1.0), show_width(400.0), show_height(400.0)
{
	type = Gray;
}

QWX_ScaleImage::QWX_ScaleImage(int _show_width, int _show_height) :Ox(0), Oy(0), width(_show_width), height(_show_height), k(1.0), show_width(_show_width), show_height(_show_height)
{
	type = Gray;
}

void QWX_ScaleImage::init_resize_first()
{
	switch (type)
	{
	case Gray:
		image = imread("zoro.jpg", 0);
		break;
	case RGB:
		image = imread("zoro.jpg");
		cvtColor(image, image, CV_BGR2RGB);//�任����ͨ����Mat��QImage�����ݽṹ����
		break;
	default:
		break;
	}
	Ox = 0;
	Oy = 0;
	k = 1.0;
	//resized = image.clone();
	image.copyTo(resized);
}

void QWX_ScaleImage::init_cut_first(const Mat &_src)
{
	_src.copyTo(image);
	Ox = 0;
	Oy = 0;
	//��ͼ�����ŵ���ȫ����ʾ
	k = min(show_width / image.cols, show_height / image.rows);
	width = show_width / k;
	height = show_height / k;
	resize(image, resized, Size(), k, k);
}

void QWX_ScaleImage::init_cut_first(String _filename)
{
	switch (type)
	{
	case Gray:
		image = imread(_filename, 0);
		//image = Mat(400, 400, CV_8UC1, Scalar(128));
		break;
	case RGB:
		image = imread(_filename);
		cvtColor(image, image, CV_BGR2RGB);//�任����ͨ����Mat��QImage�����ݽṹ����
		break;
	default:
		break;
	}	
	
	/*k = 400.0 / image.cols;
	if (k <= 400.0 / image.rows)
	{
		Oy
	}*/
	Ox = 0;
	Oy = 0;
	//��ͼ�����ŵ���ȫ����ʾ
	k = min(show_width / image.cols, show_height / image.rows);
	width = show_width / k;
	height = show_height / k;
	resize(image, resized, Size(), k, k);
	//copyMakeBorder(resized,)
}

bool QWX_ScaleImage::scale_resize_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src)
{
	Mat out(400, 400, CV_8UC3, Scalar(255, 255, 255));//�����������ź��ͼ��
	k *= _scale_k;//�ı����ԭͼ��ı���ϵ��
	resize(image, resized, Size(), k, k);//����ͼ��
	int position_x = (Ox + width*_position_kx)*_scale_k, 
		position_y = (Oy + height*_position_ky)*_scale_k;//�������λ��ָ������ص���ԭͼ������ϵ�е�����
	Ox = position_x - 400 * _position_kx;
	Oy = position_y - 400 * _position_ky;//�����и��������Ͻ�����λ��
	//������Ҫ����������
	int start_image_x = max(Ox, 0), start_image_y = max(Oy, 0),
		end_image_x = min(Ox + 400, resized.cols), end_image_y = min(Oy + 400, resized.rows);
	int start_out_x = Ox < start_image_x ? -Ox : 0, start_out_y = Oy < start_image_y ? -Oy : 0;
	//Ԫ�ؿ���
	for (int i = start_image_y, x = start_out_y; i < end_image_y; i++, x++)
	{
		for (int j = start_image_x, y = start_out_x; j < end_image_x; j++, y++)
		{
			//����ÿ��Ԫ�أ������Ƚ��������ĳ�memcpy�ڴ濽��
			out.at<Vec3b>(x, y) = resized.at<Vec3b>(i, j);
		}
	}
	out.copyTo(_src);

	return true;
}

bool QWX_ScaleImage::scale_cut_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src)
{
	k *= _scale_k;//�ı����ԭͼ��ı���ϵ��
	int position_x = Ox + width*_position_kx,
		position_y = Oy + height*_position_ky;//�������λ��ָ������ص���ԭͼ������ϵ�е�����
	width = show_width / k;
	height = show_height / k;//���´˴��и�Ŀ�͸�
	if (width == 0 || height == 0)
	{
		k /= _scale_k;
		return false;//�����ű������󣬵����и��͸�����ȡ��Ϊ0�����ش��󣬲������Ŵ�
	}
	Ox = ceil(position_x - width*_position_kx);
	Oy = ceil(position_y - height*_position_ky);//�����и��������Ͻ�����λ�ã�����ȡ������������ͼ������ƫ�Ƶ�����
	Mat cuted;
	switch (type)
	{
	case Gray:
		cuted = Mat(height, width, CV_8UC1, Scalar(255));//���������и���ͼ��
		break;
	case RGB:
		cuted = Mat(height, width, CV_8UC3, Scalar(255, 255, 255));//���������и���ͼ��
		break;
	default:
		break;
	}	
	//������Ҫ����������
	int start_image_x = max(Ox, 0), start_image_y = max(Oy, 0),
		end_image_x = min(Ox + width, image.cols), end_image_y = min(Oy + height, image.rows);
	int start_cut_x = Ox < start_image_x ? -Ox : 0, 
		start_cut_y = Oy < start_image_y ? -Oy : 0;
	//Ԫ�ؿ���
	for (int i = start_image_y, x = start_cut_y; i < end_image_y; i++, x++)
	{
		for (int j = start_image_x, y = start_cut_x; j < end_image_x; j++, y++)
		{
			//����ÿ��Ԫ�أ������Ƚ��������ĳ�memcpy�ڴ濽��
			switch (type)
			{
			case Gray:
				cuted.at<uchar>(x, y) = image.at<uchar>(i, j);
				//(Vec3b*)(cuted.data+i*cuted.step+
				break;
			case RGB:
				cuted.at<Vec3b>(x, y) = image.at<Vec3b>(i, j);
				//(Vec3b*)(cuted.data+i*cuted.step+
				break;
			default:
				break;
			}
			
		}
	}
	resize(cuted, resized, Size(show_width, show_height), 0, 0, INTER_NEAREST);//����
	resized.copyTo(_src);

	return true;
}

Point QWX_ScaleImage::QWX_get_position(double _position_kx, double _position_ky)
{
	int position_x = Ox + width*_position_kx,
		position_y = Oy + height*_position_ky;//�������λ��ָ������ص���ԭͼ������ϵ�е�����
	return Point(position_x, position_y);
}

QImage QWX_ScaleImage::QWX_Mat2QImage(const Mat &_mat)
{
	uchar *pcv = (uchar*)_mat.data;
	QImage out;
	switch (type)
	{
	case Gray:
		out = QImage(pcv, _mat.cols, _mat.rows, _mat.step, QImage::Format_Grayscale8);
		break;
	case RGB:
		out = QImage(pcv, _mat.cols, _mat.rows, _mat.step, QImage::Format_RGB888);
		break;
	default:
		break;
	}
	return out;
}
