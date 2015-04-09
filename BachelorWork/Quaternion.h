#pragma once
#include "Helpers.h"

class Quaternion
{
private:
	double x;
	double y;
	double z;
	double w;
public:
	Quaternion();
	Quaternion(double x_, double y_, double z_, double w_);
	~Quaternion();

	double Lenght() const;
	
	void Normalize();
	Quaternion getNormalize() const;

	void Conjugate();
	Quaternion getConjugate() const;

	Quaternion operator*(Quaternion right) const;
};

