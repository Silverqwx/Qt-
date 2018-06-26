#ifndef SCALEIMAGE
#define SCALEIMAGE

#include <opencv2/opencv.hpp>

using namespace cv;

class ScaleImage
{
public:
	Mat image;
	Mat resized;
	int Ox, Oy, width, height;
	double k;
	ScaleImage();
	void init_resize_first();
	void init_cut_first();
	bool scale_resize_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src);
	bool scale_cut_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src);
};

#endif // !SCALEIMAGE
