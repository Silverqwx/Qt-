#include "ScaleImage.h"

ScaleImage::ScaleImage() :Ox(0), Oy(0), width(400), height(400), k(1.0)
{
	/*Ox = (image.cols - 400) / 2;
	Oy = (image.rows - 400) / 2;*/
}

void ScaleImage::init_resize_first()
{
	image = imread("zoro.jpg");
	cvtColor(image, image, CV_BGR2RGB);
	Ox = 0;
	Oy = 0;
	k = 1.0;
	//resized = image.clone();
	image.copyTo(resized);
}

void ScaleImage::init_cut_first()
{
	image = imread("zoro.jpg");
	cvtColor(image, image, CV_BGR2RGB);
	/*k = 400.0 / image.cols;
	if (k <= 400.0 / image.rows)
	{
		Oy
	}*/
	Ox = 0;
	Oy = 0;
	k = min(400.0 / image.cols, 400.0 / image.rows);
	width = 400.0 / k;
	height = 400.0 / k;
	resize(image, resized, Size(), k, k);
}

bool ScaleImage::scale_resize_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src)
{
	Mat out(400, 400, CV_8UC3, Scalar(255, 255, 255));
	k *= _scale_k;
	resize(image, resized, Size(), k, k);
	int position_x = (Ox + width*_position_kx)*_scale_k, position_y = (Oy + height*_position_ky)*_scale_k;
	Ox = position_x - 400 * _position_kx;
	Oy = position_y - 400 * _position_ky;
	int start_image_x = max(Ox, 0), start_image_y = max(Oy, 0),
		end_image_x = min(Ox + 400, resized.cols), end_image_y = min(Oy + 400, resized.rows);
	int start_out_x = Ox < start_image_x ? -Ox : 0, start_out_y = Oy < start_image_y ? -Oy : 0;
	for (int i = start_image_y, x = start_out_y; i < end_image_y; i++, x++)
	{
		for (int j = start_image_x, y = start_out_x; j < end_image_x; j++, y++)
		{
			/*out.at<Vec3b>(x, y)[0] = resized.at<Vec3b>(i, j)[0];
			out.at<Vec3b>(x, y)[1] = resized.at<Vec3b>(i, j)[1];
			out.at<Vec3b>(x, y)[2] = resized.at<Vec3b>(i, j)[2];*/
			out.at<Vec3b>(x, y) = resized.at<Vec3b>(i, j);
		}
	}
	out.copyTo(_src);

	return true;
}

bool ScaleImage::scale_cut_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src)
{
	//Mat out;
	k *= _scale_k;
	int position_x = Ox + width*_position_kx,
		position_y = Oy + height*_position_ky;
	width = 400.0 / k;
	height = 400.0 / k;
	if (width == 0 || height == 0)
	{
		k /= _scale_k;
		return false;
	}
	Ox = ceil(position_x - width*_position_kx);
	Oy = ceil(position_y - height*_position_ky);
	Mat cuted(height, width, CV_8UC3, Scalar(255, 255, 255));
	int start_image_x = max(Ox, 0), start_image_y = max(Oy, 0),
		end_image_x = min(Ox + width, image.cols), end_image_y = min(Oy + height, image.rows);
	int start_cut_x = Ox < start_image_x ? -Ox : 0, 
		start_cut_y = Oy < start_image_y ? -Oy : 0;
	for (int i = start_image_y, x = start_cut_y; i < end_image_y; i++, x++)
	{
		for (int j = start_image_x, y = start_cut_x; j < end_image_x; j++, y++)
		{
			cuted.at<Vec3b>(x, y) = image.at<Vec3b>(i, j);
		}
	}
	resize(cuted, _src, Size(400,400));

	return true;
}