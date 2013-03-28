#include "point.h"


point::point(void){
	point(0);
}

point::point(int size){
	data.assign(size, 0.f);
}


point::~point(void){
}

float point::l1_norm(){
	float sum = 0.f;
	for(size_t i = 0; i < data.size(); ++i){
		sum += abs(data[i]);
	}
	return sum;
}

float point::l2_norm(){
	float sum = 0.f;
	for(size_t i = 0; i < data.size(); ++i){
		sum += data[i] * data[i];
	}
	return sqrtf(sum);
}

void point::l1_normalize(){
	float norm = l1_norm();
	if(norm == 0.f){
		std::cerr << "0 norm" << std::endl;
		exit(1);
	}
	for(size_t i = 0; i < data.size(); ++i){
		data[i] /= norm;
	}
}

void point::l2_normalize(){
	float norm = l2_norm();
	if(norm == 0.f){
		std::cerr << "0 norm" << std::endl;
		exit(1);
	}
	for(size_t i = 0; i < data.size(); ++i){
		data[i] /= norm;
	}
}

float point::inner_prod(const point& p){
	float sum = 0.f;
	if(data.size() != p.data.size()){
		std::cerr << "dimension not match" << std::endl;
		exit(1);
	}
	for(size_t i = 0; i < data.size(); ++i){
		sum += data[i] * p.data[i];
	}
	return sum;
}
