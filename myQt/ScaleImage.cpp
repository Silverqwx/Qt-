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
		cvtColor(image, image, CV_BGR2RGB);//变换三个通道，Mat和QImage的数据结构区别
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
	//把图像缩放到能全部显示
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
		cvtColor(image, image, CV_BGR2RGB);//变换三个通道，Mat和QImage的数据结构区别
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
	//把图像缩放到能全部显示
	k = min(show_width / image.cols, show_height / image.rows);
	width = show_width / k;
	height = show_height / k;
	resize(image, resized, Size(), k, k);
	//copyMakeBorder(resized,)
}

bool QWX_ScaleImage::scale_resize_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src)
{
	Mat out(400, 400, CV_8UC3, Scalar(255, 255, 255));//用来保存缩放后的图像
	k *= _scale_k;//改变相对原图像的比例系数
	resize(image, resized, Size(), k, k);//缩放图像
	int position_x = (Ox + width*_position_kx)*_scale_k, 
		position_y = (Oy + height*_position_ky)*_scale_k;//计算鼠标位置指向的像素点在原图像坐标系中的坐标
	Ox = position_x - 400 * _position_kx;
	Oy = position_y - 400 * _position_ky;//更新切割区域左上角坐标位置
	//计算需要拷贝的区域
	int start_image_x = max(Ox, 0), start_image_y = max(Oy, 0),
		end_image_x = min(Ox + 400, resized.cols), end_image_y = min(Oy + 400, resized.rows);
	int start_out_x = Ox < start_image_x ? -Ox : 0, start_out_y = Oy < start_image_y ? -Oy : 0;
	//元素拷贝
	for (int i = start_image_y, x = start_out_y; i < end_image_y; i++, x++)
	{
		for (int j = start_image_x, y = start_out_x; j < end_image_x; j++, y++)
		{
			//拷贝每个元素，这样比较慢，待改成memcpy内存拷贝
			out.at<Vec3b>(x, y) = resized.at<Vec3b>(i, j);
		}
	}
	out.copyTo(_src);

	return true;
}

bool QWX_ScaleImage::scale_cut_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src)
{
	k *= _scale_k;//改变相对原图像的比例系数
	int position_x = Ox + width*_position_kx,
		position_y = Oy + height*_position_ky;//计算鼠标位置指向的像素点在原图像坐标系中的坐标
	width = show_width / k;
	height = show_height / k;//更新此次切割的宽和高
	if (width == 0 || height == 0)
	{
		k /= _scale_k;
		return false;//若缩放比例过大，导致切割宽和高向下取整为0，返回错误，不继续放大
	}
	Ox = ceil(position_x - width*_position_kx);
	Oy = ceil(position_y - height*_position_ky);//更新切割区域左上角坐标位置，向上取整，否则会出现图像朝右下偏移的现象
	Mat cuted;
	switch (type)
	{
	case Gray:
		cuted = Mat(height, width, CV_8UC1, Scalar(255));//用来保存切割后的图像
		break;
	case RGB:
		cuted = Mat(height, width, CV_8UC3, Scalar(255, 255, 255));//用来保存切割后的图像
		break;
	default:
		break;
	}	
	//计算需要拷贝的区域
	int start_image_x = max(Ox, 0), start_image_y = max(Oy, 0),
		end_image_x = min(Ox + width, image.cols), end_image_y = min(Oy + height, image.rows);
	int start_cut_x = Ox < start_image_x ? -Ox : 0, 
		start_cut_y = Oy < start_image_y ? -Oy : 0;
	//元素拷贝
	for (int i = start_image_y, x = start_cut_y; i < end_image_y; i++, x++)
	{
		for (int j = start_image_x, y = start_cut_x; j < end_image_x; j++, y++)
		{
			//拷贝每个元素，这样比较慢，待改成memcpy内存拷贝
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
	resize(cuted, resized, Size(show_width, show_height), 0, 0, INTER_NEAREST);//缩放
	resized.copyTo(_src);

	return true;
}

Point QWX_ScaleImage::QWX_get_position(double _position_kx, double _position_ky)
{
	int position_x = Ox + width*_position_kx,
		position_y = Oy + height*_position_ky;//计算鼠标位置指向的像素点在原图像坐标系中的坐标
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
