#pragma once
#include <iostream>
#include <vector>

class point
{
public:
	point();
	point(int size);
	virtual ~point(void);
	float l1_norm();
	float l2_norm();
	void l1_normalize();
	void l2_normalize();
	float inner_prod(const point& p);
	std::vector<float> data;
};

