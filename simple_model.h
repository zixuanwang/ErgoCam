#pragma once

#include "generative_model.h"
class simple_model: public generative_model
{
public:
	simple_model(void);
	virtual ~simple_model(void);
	virtual float get_probability(const state& s, const feature_vector& observation);
};

