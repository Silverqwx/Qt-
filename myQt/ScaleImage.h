#ifndef SCALEIMAGE
#define SCALEIMAGE

#include <opencv2/opencv.hpp>
#include <string>
#include <QImage>

using namespace cv;

enum QWX_ImageType
{
	Gray,
	RGB
};

class QWX_ScaleImage
{
public:
	QWX_ImageType type;//图像类型
	Mat image;//保存载入的原图像
	Mat resized;//保存尺度变换后的图像
	//保存上一次的切割区域信息
	//Ox，Oy为在原图像坐标系中的左上角坐标
	//width，height为切割区域的宽和高
	int Ox, Oy, width, height;
	float show_width, show_height;
	double k;//缩放的比例系数，表示缩放后的图像为原图像的多少倍
	QWX_ScaleImage();
	QWX_ScaleImage(int _show_width, int _show_height);
	void init_resize_first();//先缩放后切割方式的初始化函数
	void init_cut_first(const Mat &_src);
	void init_cut_first(String _filename);//先切割后缩放方式的初始化函数
	//先缩放后切割方式的尺度变换（缩放）函数
	//_position_kx，_position_ky代表鼠标位置在标签中的相对位置（比例关系）,为坐标值与宽或高的比值
	//_scale_k为此次缩放比例系数
	//_src用来返回变换后图像
	bool scale_resize_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src);
	//先切割后缩放方式的尺度变换（缩放）函数
	//_position_kx，_position_ky代表鼠标位置在标签中的相对位置（比例关系）,为坐标值与宽或高的比值
	//_scale_k为此次缩放比例系数
	//_src用来返回变换后图像
	bool scale_cut_first(double _position_kx, double _position_ky, double _scale_k, Mat &_src);
	Point QWX_get_position(double _position_kx, double _position_ky);
	QImage QWX_Mat2QImage(const Mat &_mat);
};

#endif // !SCALEIMAGE
