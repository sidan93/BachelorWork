#include "Vector.h"


Vector::Vector(void)
{
	init(0,0,0,1);
}
Vector::Vector(float x, float y)
{
	init(x,y,0,1);
}
Vector::Vector(float x, float y, float z)
{
	init(x,y,z,1);
}
Vector::Vector(float x, float y, float z, float w)
{
	init(x,y,z,w);
}

float& Vector::X()
{
	return _x;
}
float& Vector::Y()
{
	return _y;
}
float& Vector::Z()
{
	return _z;
}
float& Vector::W()
{
	return _w;
}

void Vector::init(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

Vector::~Vector(void)
{
}
