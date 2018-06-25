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
	//void init();
	Mat scale(int _wheel_x, int _wheel_y, double _position_kx, double _position_ky, double _scale_k);

};

#endif // !SCALEIMAGE
