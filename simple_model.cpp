#include "simple_model.h"


simple_model::simple_model(void)
{
}


simple_model::~simple_model(void)
{
}

float simple_model::get_probability(const state& s, const feature_vector& observation){
	return 1.f;
}