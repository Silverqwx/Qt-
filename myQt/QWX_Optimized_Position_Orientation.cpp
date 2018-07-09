#include "QWX_Optimized_Position_Orientation.h"

cv::Mat cv::getGaborKernel(Size ksize, double sigma, double theta,
	double lambd, double gamma, double psi, int ktype)
{
	//获取两个数学遍历sigma_x和sigma_y，方便后面的计算，没有特殊含义
	double sigma_x = sigma;
	double sigma_y = sigma / gamma;

	int nstds = 3;//为后面的当ksize出现负数时计算核函数窗口大小提供参数
	int xmin, xmax, ymin, ymax;
	double c = cos(theta), s = sin(theta);
	//当ksize的width和height没有负数时，取其一半给xmax和ymax
	if (ksize.width > 0)
		xmax = ksize.width / 2;
	else
		xmax = cvRound(std::max(fabs(nstds*sigma_x*c), fabs(nstds*sigma_y*s)));

	if (ksize.height > 0)
		ymax = ksize.height / 2;
	else
		ymax = cvRound(std::max(fabs(nstds*sigma_x*s), fabs(nstds*sigma_y*c)));

	xmin = -xmax;
	ymin = -ymax;

	CV_Assert(ktype == CV_32F || ktype == CV_64F);
	//核函数矩阵，ymax-ymin+1和xmax-xmin+1是为保证核函数矩阵是长和宽都是奇数
	Mat kernel(ymax - ymin + 1, xmax - xmin + 1, ktype);
	double scale = 1;
	//方便计算，可以自己带入到后面的v的计算公式中会发现Gabor滤波器的实数部分的公式
	double ex = -0.5 / (sigma_x*sigma_x);
	double ey = -0.5 / (sigma_y*sigma_y);
	double cscale = CV_PI * 2 / lambd;

	for (int y = ymin; y <= ymax; y++)
	for (int x = xmin; x <= xmax; x++)
	{
		double xr = x*c + y*s;
		double yr = -x*s + y*c;
		//计算公式，Opencv这里获取的是Gabor滤波器的实数部分
		double v = scale*exp(ex*xr*xr + ey*yr*yr)*cos(cscale*xr + psi);
		if (ktype == CV_32F)
			kernel.at<float>(ymax - y, xmax - x) = (float)v;
		else
			kernel.at<double>(ymax - y, xmax - x) = v;
	}

	return kernel;
}

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
	int kernel_half_diagonal_x = ceil(kernel_mid_x*sqrtf(2.0)),
		kernel_half_diagonal_y = ceil(kernel_mid_y*sqrtf(2.0));
	if (_u<kernel_half_diagonal_y || _u >= _src.rows - kernel_half_diagonal_y || _v<kernel_half_diagonal_x || _v >= _src.cols - kernel_half_diagonal_x)
	{
		//cout << "太过靠近边缘，不进行处理！！！" << endl;
		return -1.0;
	}
	/*if (_u >= 610)
		int kkk = 0;*/
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

vector<float> QWX_Optimized_Position_Orientation::QWX_rotate(float _theta)
{
	int kernel_cols = kernel.cols,
		kernel_rows = kernel.rows;
	vector<float> rotated_kernel;//(kernel_cols * kernel_rows * 3);
	for (float x = 0, i = -kernel_mid_x; x < kernel_cols; x++, i++)
	{
		for (float y = 0, j = -kernel_mid_y; y < kernel_rows; y++, j++)
		{
			int rotated_x = round(i*cos(_theta) - j*sin(_theta));
			int rotated_y = round(i*sin(_theta) + j*cos(_theta));
			/*if (rotated_x>20 || rotated_y >20)
				int kkk = 0;*/
			rotated_kernel.push_back(rotated_x);
			rotated_kernel.push_back(rotated_y);
			rotated_kernel.push_back(kernel.at<float>(y, x));
		}
	}

	return rotated_kernel;
}

float QWX_Optimized_Position_Orientation::QWX_convolution(const Mat &_src, const vector<float> &_rotated_kernel, int _u, int _v)
{
	float sum = 0.0;
	for (int i = 0; i < _rotated_kernel.size(); i += 3)
	{
		/*if (_rotated_kernel[i + 1] < -kernel_mid_y || _rotated_kernel[i + 1] >= kernel_mid_y || _rotated_kernel[i] < -kernel_mid_x || _rotated_kernel[i] >= kernel_mid_x)
			continue;*/
		float temp1 = _rotated_kernel[i + 2];
		/*if (temp1 < 0)
			temp1 = 0;*/
		sum += temp1 * _src.at<uchar>(_u + _rotated_kernel[i + 1], _v + _rotated_kernel[i]);
	}

	return sum;
}

float QWX_Optimized_Position_Orientation::QWX_getvalue(const Mat &_src, int _u, int _v, float _theta)
{
	vector<float> rotated_kernel = QWX_rotate(_theta);
	float value = QWX_convolution(_src, rotated_kernel, _u, _v);

	return value;
}

Mat QWX_Optimized_Position_Orientation::QWX_gethist(const Mat &_src, int _u, int _v)
{	
	Mat out(100, 360, CV_8UC1, Scalar(0));
	int kernel_half_diagonal_x = ceil(kernel_mid_x*sqrtf(2.0)),
		kernel_half_diagonal_y = ceil(kernel_mid_y*sqrtf(2.0));
	if (_u<kernel_half_diagonal_y || _u >= _src.rows - kernel_half_diagonal_y || _v<kernel_half_diagonal_x || _v >= _src.cols - kernel_half_diagonal_x)
	{
		//cout << "太过靠近边缘，不进行处理！！！" << endl;
		return out;
	}
	vector<int> f(360);
	float fmax = 0.0,
		fmin = 0.0;
	float r = CV_PI / 180;
	for (int i = 0; i < 360; i++)
	{
		float temp = QWX_getvalue(_src, _u, _v, i*r);
		f[i] = temp;
		if (temp>fmax) fmax = temp;
		else if (temp < fmin) fmin = temp;
	}
	float frange = fmax - fmin;
	if (frange == 0.0)
		return out;
	for (int i = 0; i < 360; i++)
	{
		int h = 99 - (f[i] - fmin) / frange * 99;
		if (h < 0)
			int j = 0;
		out.at<uchar>(h, i) = 255;
	}

	return out;
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

void QWX_Optimized_Position_Orientation::consGabor()
{
	//Mat temp = getGaborKernel(Size(31, 31), 10, 0, 20, 1, 1.5, CV_32F);
	Mat temp = getGaborKernel(Size(15, 15), 2 * CV_PI, 0, 15, 0.5, 0, CV_32F);
	temp.copyTo(kernel);
	kernel_mid_x = kernel.cols / 2.0 - 0.5;
	kernel_mid_y = kernel.rows / 2.0 - 0.5;
	imshow("gabor", kernel);
}