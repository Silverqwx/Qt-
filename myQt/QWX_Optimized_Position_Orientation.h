#ifndef QWX_OPTIMIZED_POSITION_ORIENTATION
#define QWX_OPTIMIZED_POSITION_ORIENTATION

#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>


using namespace std;
using namespace cv;

struct QWX_Ftheta
{
	float theta, value;
	QWX_Ftheta(float _theta, float _value) :theta(_theta), value(_value)
	{}
	/*bool operator<(const QWX_Ftheta &another)
	{
	return value < another.value;
	}
	bool operator>(const QWX_Ftheta &another)
	{
	return value > another.value;
	}*/
};

struct QWX_Ftheta_compare
{
	bool operator()(const QWX_Ftheta &L, const QWX_Ftheta &R) const
	{
		return L.value < R.value;
	}
};

class QWX_Optimized_Position_Orientation
{
	Mat kernel;
	float kernel_mid_x,
		kernel_mid_y;
	float resolution,
		min_extremum_range;
public:
	QWX_Optimized_Position_Orientation();
	QWX_Optimized_Position_Orientation(const Mat &_kernel, float _resolution = 1.0, float _min_extremum_range = 20.0);
	~QWX_Optimized_Position_Orientation();
	void QWX_init(const Mat &_kernel, float _resolution = 1.0, float _min_extremum_range = 20.0);
	float QWX_compute(const Mat &_src, int _u, int _v, int _radius = 0);
	Mat QWX_gethist(const Mat &_src, int _u, int _v);
private:
	vector<int> QWX_rotate(float _theta);
	float QWX_convolution(const Mat &_src, const vector<int> &_rotated_kernel, int _u, int _v);
	float QWX_getvalue(const Mat &_src, int _u, int _v, float _theta);
	QWX_Ftheta QWX_dichotomy(const Mat &_src, int _u, int _v, float L_theta, float R_theta);
	
};


#endif // !QWX_OPTIMIZED_POSITION_ORIENTATION



