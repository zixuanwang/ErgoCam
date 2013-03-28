#pragma once

#include "feature_vector.h"
#include "state.h"
class generative_model
{
public:
	generative_model(void);
	virtual ~generative_model(void);
	virtual float get_probability(const state& s, const feature_vector& observation) = 0;
};

