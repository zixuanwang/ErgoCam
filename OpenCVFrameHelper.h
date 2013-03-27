#pragma once
#include <Windows.h>
#include <NuiApi.h>
#include <FaceTrackLib.h>
#include <opencv2/opencv.hpp>
#include <QImage>
class OpenCVFrameHelper
{
public:
	OpenCVFrameHelper(void);
	~OpenCVFrameHelper(void);
	static QImage mat2QImage(const cv::Mat4b& src);
	static void draw_string(cv::Mat& image, const std::string& text);
};

