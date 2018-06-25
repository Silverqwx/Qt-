#include "ScaleImage.h"

ScaleImage::ScaleImage() :Ox(0), Oy(0), width(400), height(400), k(1.0)
{
	Ox = (image.cols - 400) / 2;
	Oy = (image.rows - 400) / 2;
}

Mat ScaleImage::scale(int _wheel_x, int _wheel_y, double _position_kx, double _position_ky, double _scale_k)
{
	Mat out(400, 400, CV_8UC3, Scalar(255, 255, 255));
	k *= _scale_k;
	resize(image, resized, Size(), k, k);
	//int x = _x*_k, y = _y*_k;
	//int wheel_x = _wheel_x*_scale_k, wheel_y = _wheel_y*_scale_k;
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
			out.at<Vec3b>(x, y)[0] = resized.at<Vec3b>(i, j)[0];
			out.at<Vec3b>(x, y)[1] = resized.at<Vec3b>(i, j)[1];
			out.at<Vec3b>(x, y)[2] = resized.at<Vec3b>(i, j)[2];
		}
	}
	/*imshow("1", out);
	waitKey(0);*/

	return out;
}