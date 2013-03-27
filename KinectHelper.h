#pragma once
#include <Windows.h>
#include <NuiApi.h>
#include <FaceTrackLib.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#define kinect_width 640
#define kinect_height 480

class KinectHelper
{
public:
	KinectHelper(void);
	~KinectHelper(void);
	HRESULT initKinect();
	void getVideoFrame();
	void getDepthFrame();
	IFTImage* getVideoBuffer(){return m_videoBuffer;}
	IFTImage* getDrawBuffer(){return m_drawBuffer;}
	IFTImage* getDepthBuffer(){return m_depthBuffer;}
	bool getIsFaceTracked(){return m_isFaceTracked;}
	cv::Mat video2Mat(IFTImage* pBuffer);
	cv::Mat depth2Mat(IFTImage* pBuffer);
	void trackFace();
	void processFaceModel();
	HRESULT visualizeFaceModel();
	std::vector<cv::Point2f> getLandmarkPoints(){return m_landmarkPoints;}
	HRESULT get3DPose(FLOAT *pScale, FLOAT rotationXYZ[3], FLOAT translationXYZ[3]){return m_pFTResult->Get3DPose(pScale, rotationXYZ, translationXYZ);}
	std::vector<float> getAUCoefficients();
private:
	FLOAT m_zoomFactor;
	POINT m_viewOffset;
	FT_CAMERA_CONFIG m_videoCameraConfig;
	FT_CAMERA_CONFIG m_depthCameraConfig;
	HANDLE m_videoStream;
	HANDLE m_depthStream;
	IFTImage* m_videoBuffer;
	IFTImage* m_depthBuffer;
	IFTImage* m_drawBuffer;
	IFTFaceTracker* m_pFT;
	IFTResult* m_pFTResult;
	bool m_isFaceTracked;
	std::vector<cv::Point2f> m_landmarkPoints;
};

