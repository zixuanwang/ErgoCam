#include "ergocam.h"

ErgoCam::ErgoCam(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_kinect_helper.initKinect();
	//m_directory = "c:";
	//m_video_capture.open(1); // change device index.
	m_index = 0;
	m_sample_timer = new QTimer(this);
	m_recommendation_timer = new QTimer(this);
	m_sample_timer->setInterval(30);
	m_recommendation_timer->setInterval(1000 * 60 * 10);
	connect(ui.save_directory_action, SIGNAL(triggered()), this, SLOT(save_directory()));
	connect(ui.tired_button, SIGNAL(clicked()), this, SLOT(record_tired_video()));
	connect(ui.focus_button, SIGNAL(clicked()), this, SLOT(record_focus_video()));
	connect(ui.stress_button, SIGNAL(clicked()), this, SLOT(record_stress_video()));
	connect(m_sample_timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
	connect(m_recommendation_timer, SIGNAL(timeout()), this, SLOT(recommend()));
	m_sample_timer->start();
	m_recommendation_timer->start();
	//m_out_stream.open(m_directory + "/frame.txt");
	//m_video_writer.open(m_directory + "/video.avi" , CV_FOURCC('M','P','4','2'), 30, cv::Size(640, 480));
}

void ErgoCam::closeEvent(QCloseEvent* event){
	m_out_stream.close();
}

ErgoCam::~ErgoCam()
{

}

void ErgoCam::save_directory(){
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::Directory);
	int result = dialog.exec();
	QString directory;
	if (result){
		directory = dialog.selectedFiles()[0];
		m_directory = directory.toStdString();
		m_out_stream.open(m_directory + "/frame.txt");
		m_video_writer.open(m_directory + "/video.avi" , CV_FOURCC('M','P','4','2'), 30, cv::Size(640, 480));
	}
}

void ErgoCam::record_tired_video(){
	if(m_directory.empty()){
		QMessageBox::warning(this, "Notice", "Please specify the output directory first");
		return;
	}
	ui.status_label->setText("Tired Mode.");
	m_out_stream << "tired " << m_index << std::endl;
}
void ErgoCam::record_focus_video(){
	if(m_directory.empty()){
		QMessageBox::warning(this, "Notice", "Please specify the output directory first");
		return;
	}
	ui.status_label->setText("Focus Mode.");
	m_out_stream << "focus " << m_index << std::endl;
}
void ErgoCam::record_stress_video(){
	if(m_directory.empty()){
		QMessageBox::warning(this, "Notice", "Please specify the output directory first");
		return;
	}
	ui.status_label->setText("Stress Mode.");
	m_out_stream << "stress " << m_index << std::endl;
}

void ErgoCam::update_info(){
	cv::Mat image;
	image = m_kinect_helper.video2Mat(m_kinect_helper.getVideoBuffer());
	if(m_kinect_helper.getIsFaceTracked()){
		FLOAT scale;
		FLOAT rotationXYZ[3];
		FLOAT translationXYZ[3];
		m_kinect_helper.get3DPose(&scale, rotationXYZ, translationXYZ); // get rotation and translation.
		m_kinect_helper.processFaceModel(); // get landmarks
		m_kinect_helper.getAUCoefficients(); // get AU coefficients
		m_face_feature.calc_count(m_kinect_helper.getLandmarkPoints(), translationXYZ[2] * translationXYZ[2]); // compute yawn and blink
		ui.track_icon_label->setPixmap(QPixmap(QString::fromUtf8(":/ErgoCam/Resources/green.png")));
		ui.track_text_label->setText("Tracking");
		ui.pitch_label->setText(QString::number(rotationXYZ[0]));
		ui.yaw_label->setText(QString::number(rotationXYZ[1]));
		ui.roll_label->setText(QString::number(rotationXYZ[2]));
		ui.distance_label->setText(QString::number(translationXYZ[2]));
		ui.yawn_label->setText(QString::number(m_face_feature.get_yawn_count()));
		if(ui.model_checkbox->isChecked()){
			m_kinect_helper.visualizeFaceModel();
			image =  m_kinect_helper.video2Mat(m_kinect_helper.getDrawBuffer());
		}
		if(ui.landmark_checkbox->isChecked()){
			std::vector<cv::Point2f>& landmark_points = m_kinect_helper.getLandmarkPoints();
			for(size_t i = 0; i < landmark_points.size(); ++i){
				cv::circle(image, landmark_points[i], 1, cv::Scalar(0,0,255,0), -1, CV_AA);
			}
		}
	}else{
		ui.track_icon_label->setPixmap(QPixmap(QString::fromUtf8(":/ErgoCam/Resources/red.png")));
		ui.track_text_label->setText("Not Tracking");
		ui.pitch_label->setText("");
		ui.yaw_label->setText("");
		ui.roll_label->setText("");
		ui.distance_label->setText("");
	}
	ui.preview_label->setPixmap(QPixmap::fromImage(OpenCVFrameHelper::mat2QImage(image)));
}

void ErgoCam::timer_timeout(){
	m_kinect_helper.trackFace();
	update_info();
}

void ErgoCam::recommend(){

}