#include "QWX_Optimized_Position_Orientation.h"

QWX_Optimized_Position_Orientation::QWX_Optimized_Position_Orientation()
{
	kernel = Mat::zeros(3, 3, CV_8UC1);
	resolution = 1.0;
	min_extremum_range = 20.0;
}

QWX_Optimized_Position_Orientation::QWX_Optimized_Position_Orientation(const Mat &_kernel, float _resolution, float _min_extremum_range)
{
	QWX_init(_kernel, _resolution, _min_extremum_range);
}

QWX_Optimized_Position_Orientation::~QWX_Optimized_Position_Orientation()
{}

void QWX_Optimized_Position_Orientation::QWX_init(const Mat &_kernel, float _resolution, float _min_extremum_range)
{
	_kernel.copyTo(kernel);
	kernel_mid_x = kernel.cols / 2.0 - 0.5;
	kernel_mid_y = kernel.rows / 2.0 - 0.5;
	resolution = _resolution;
	min_extremum_range = _min_extremum_range;
}

float QWX_Optimized_Position_Orientation::QWX_compute(const Mat &_src, int _u, int _v, int _radius)
{
	if (_u<kernel_mid_y || _u>=_src.rows - kernel_mid_y || _v<kernel_mid_x || _v>=_src.cols - kernel_mid_x)
	{
		//cout << "太过靠近边缘，不进行处理！！！" << endl;
		return -1.0;
	}
	float radian_range = min_extremum_range*CV_PI / 180;
	priority_queue<QWX_Ftheta, vector<QWX_Ftheta>, QWX_Ftheta_compare> extremum_list;
	for (float theta = 0.0; theta < 2 * CV_PI; theta += radian_range)
	{
		QWX_Ftheta extremum = QWX_dichotomy(_src, _u, _v, theta, theta + radian_range);
		extremum_list.push(extremum);
	}
	float omax = extremum_list.top().theta;
	//omax = omax * 180 / CV_PI;

	return omax;
}

vector<int> QWX_Optimized_Position_Orientation::QWX_rotate(float _theta)
{
	int kernel_cols = kernel.cols,
		kernel_rows = kernel.rows;
	vector<int> rotated_kernel;//(kernel_cols * kernel_rows * 3);
	for (float x = 0, i = -kernel_mid_x; x < kernel_cols; x++, i++)
	{
		for (float y = 0, j = -kernel_mid_y; y < kernel_rows; y++, j++)
		{
			int rotated_x = round(i*cos(_theta) - j*sin(_theta));
			int rotated_y = round(i*sin(_theta) + j*cos(_theta));
			rotated_kernel.push_back(rotated_x);
			rotated_kernel.push_back(rotated_y);
			rotated_kernel.push_back(kernel.at<uchar>(y, x));
		}
	}

	return rotated_kernel;
}

float QWX_Optimized_Position_Orientation::QWX_convolution(const Mat &_src, const vector<int> &_rotated_kernel, int _u, int _v)
{
	float sum = 0.0;
	for (int i = 0; i < _rotated_kernel.size(); i += 3)
	{
		if (_rotated_kernel[i + 1] < -kernel_mid_y || _rotated_kernel[i + 1] >= kernel_mid_y || _rotated_kernel[i] < -kernel_mid_x || _rotated_kernel[i] >= kernel_mid_x)
			continue;
		sum += _rotated_kernel[i + 2] * _src.at<uchar>(_u + _rotated_kernel[i + 1], _v + _rotated_kernel[i]);
	}

	return sum;
}

float QWX_Optimized_Position_Orientation::QWX_getvalue(const Mat &_src, int _u, int _v, float _theta)
{
	vector<int> rotated_kernel = QWX_rotate(_theta);
	float value = QWX_convolution(_src, rotated_kernel, _u, _v);

	return value;
}

QWX_Ftheta QWX_Optimized_Position_Orientation::QWX_dichotomy(const Mat &_src, int _u, int _v, float L_theta, float R_theta)
{
	float L_value = QWX_getvalue(_src, _u, _v, L_theta),
		R_value = QWX_getvalue(_src, _u, _v, R_theta);
	int num = ceil(log2f(min_extremum_range / resolution));
	for (int i = 0; i < num; i++)
	{
		float M_theta = (L_theta + R_theta) / 2;
		float M_value = QWX_getvalue(_src, _u, _v, M_theta);
		if (L_value < R_value)
		{
			L_value = M_value;
			L_theta = M_theta;
		}
		else
		{
			R_value = M_value;
			R_theta = M_theta;
		}
	}
	QWX_Ftheta result = L_value > R_value ? QWX_Ftheta(L_theta * 180 / CV_PI, L_value) : QWX_Ftheta(R_theta * 180 / CV_PI, R_value);
	
	return result;
}