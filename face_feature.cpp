#include "face_feature.h"

face_feature::face_feature(void)
{
	// hard coding indices.
	// see http://msdn.microsoft.com/en-us/library/jj130970.aspx
	int _left_eye_indices[] = {8,9,10,11,12,13,14,15};
	int _right_eye_indices[] = {7,6,5,4,3,2,1,0};
	int _mouth_indices[] = {59,58,57,56,55,54,53,52,51,50,49,48};
	int _nose_indices[] = {36,37,38,39,40,41,42,43,44,45,46,47};
	left_eye_indices.assign(_left_eye_indices, _left_eye_indices + sizeof(_left_eye_indices) / sizeof(_left_eye_indices[0]));
	right_eye_indices.assign(_right_eye_indices, _right_eye_indices + sizeof(_right_eye_indices) / sizeof(_right_eye_indices[0]));
	mouth_indices.assign(_mouth_indices, _mouth_indices + sizeof(_mouth_indices) / sizeof(_mouth_indices[0]));
	nose_indices.assign(_nose_indices, _nose_indices + sizeof(_nose_indices) / sizeof(_nose_indices[0]));
	m_blink_count = 0;
	m_yawn_count = 0;
	m_blink_trigger = false;
	m_yawn_trigger = false;
}


face_feature::~face_feature(void)
{
}

void face_feature::calc_count(const std::vector<cv::Point2f>& points, float scale){
	float mouth_area = polygon_area(points, mouth_indices);
	m_mouth_area_list.push_back(mouth_area / scale);
	int size = 5;
	int middle = size / 2;
	if(static_cast<int>(m_mouth_area_list.size()) > size){
		m_mouth_area_list.pop_front();
		std::vector<float> mouth_area_vector(m_mouth_area_list.begin(), m_mouth_area_list.end());
		std::nth_element(mouth_area_vector.begin(), mouth_area_vector.begin() + middle, mouth_area_vector.end());
		float median_mouth_area = mouth_area_vector[middle];
		// thresholding
		if(median_mouth_area > 250.f){
			m_yawn_trigger = true;
		}else if(m_yawn_trigger){
			m_yawn_trigger = false;
			++m_yawn_count;
		}
	}
}

float face_feature::polygon_area(const std::vector<cv::Point2f>& points, const std::vector<int>& indices){
	boost::geometry::model::polygon<boost::tuple<float, float> > polygon;
	for(size_t i = 0; i < indices.size(); ++i){
		boost::geometry::append(polygon,boost::make_tuple(points[indices[i]].x,points[indices[i]].y));
	}
	return boost::geometry::area(polygon);
}
