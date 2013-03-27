#include "histogram.h"


histogram::histogram(float min, float max, float step): m_min(min), m_max(max), m_step(step){
	int size = static_cast<int>((m_max - m_min) / m_step);
	if(size < 0){
		std::cerr << "error in histogram size" << std::endl;
		exit(1);
	}
	m_frequency_vector.assign(size + 1, 0.f);
}


histogram::~histogram(void){
}

void histogram::add(float value, int frequency){
	int index = static_cast<int>((value - m_min) / m_step);
	m_frequency_vector[index] += frequency;
}

void histogram::normalize(){
	float sum = 0.f;
	for(size_t i = 0; i < m_frequency_vector.size(); ++i){
		sum += m_frequency_vector[i] * m_frequency_vector[i];
	}
	sum = sqrtf(sum);
	for(size_t i = 0; i < m_frequency_vector.size(); ++i){
		m_frequency_vector[i] /= sum;
	}
}