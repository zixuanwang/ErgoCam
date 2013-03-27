#pragma once
#include <iostream>
#include <vector>
class histogram
{
public:
	histogram(float min, float max, float step); // constructor with min value, max value and step.
	~histogram(void);
	void add(float value, int frequency = 1); // add a new value to the histogram.
	void normalize(); // normalize the L2 length to be 1.
	std::vector<float> get(){return m_frequency_vector;}
private:
	float m_min;
	float m_max;
	float m_step;
	std::vector<float> m_frequency_vector;
};

