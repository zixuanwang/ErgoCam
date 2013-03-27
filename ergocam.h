#ifndef ERGOCAM_H
#define ERGOCAM_H

#include <fstream>
#include <iostream>
#include "OpenCVFrameHelper.h"
#include <opencv2/opencv.hpp>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <string>
#include <sstream>
#include "ui_ergocam.h"
#include "KinectHelper.h"
#include "face_feature.h"

class ErgoCam : public QMainWindow
{
	Q_OBJECT

public:
	ErgoCam(QWidget *parent = 0);
	~ErgoCam();
public slots:
	void save_directory();
	void record_tired_video();
	void record_focus_video();
	void record_stress_video();
	void timer_timeout();
	void recommend();
protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::ErgoCamClass ui;
	cv::VideoCapture m_video_capture;
	std::ofstream m_out_stream;
	int m_index;
	std::string m_directory;
	QTimer* m_sample_timer;
	QTimer* m_recommendation_timer;
	cv::VideoWriter m_video_writer;
	KinectHelper m_kinect_helper;
	void update_info();
	face_feature m_face_feature;
};

#endif // ERGOCAM_H
