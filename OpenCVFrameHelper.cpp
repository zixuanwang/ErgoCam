#include "OpenCVFrameHelper.h"


OpenCVFrameHelper::OpenCVFrameHelper(void)
{
}


OpenCVFrameHelper::~OpenCVFrameHelper(void)
{
}

QImage OpenCVFrameHelper::mat2QImage(const cv::Mat4b& src){
	QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
	for(int y = 0; y < src.rows; ++y){
		const cv::Vec4b* src_row = src[y];
		QRgb* dest_row = (QRgb*)dest.scanLine(y);
		for(int x = 0; x < src.cols; ++x){
			dest_row[x] = qRgba(src_row[x][2], src_row[x][1], src_row[x][0], 255);
		}
	}
	return dest;
}

void OpenCVFrameHelper::draw_string(cv::Mat& image, const std::string& text){
	cv::Size size = cv::getTextSize(text, cv::FONT_HERSHEY_COMPLEX, 0.6f, 1, NULL);
	cv::putText(image,text, cv::Point(0,size.height), cv::FONT_HERSHEY_COMPLEX,0.6f,
		CV_RGB(200,50,50),1,CV_AA);
}