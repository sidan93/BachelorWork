#include "Quaternion.h"


Quaternion::Quaternion() : Quaternion(0,0,0,0)
{
}

Quaternion::Quaternion(double x_, double y_, double z_, double w_) : x(x_), y(y_), z(z_), w(w_)
{
}

double Quaternion::Lenght() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}
void Quaternion::Normalize()
{
	double lenght = Lenght();
	x /= lenght;
	y /= lenght;
	z /= lenght;
	w /= lenght;
}
Quaternion Quaternion::getNormalize() const
{
	Quaternion q(x, y, z, w);
	q.Normalize();
	return q;
}


void Quaternion::Conjugate()
{
	x = -x;
	y = -y;
	z = -z;
}
Quaternion Quaternion::getConjugate() const
{
	Quaternion q(x, y, z, w);
	q.Conjugate();
	return q;
}

Quaternion Quaternion::operator*(Quaternion right) const
{
	double rX, rY, rZ, rW;
	rX = w * right.x + x * right.w + y * right.z - z * right.y;
	rY = w * right.y - x * right.z + y * right.w + z * right.x;
	rZ = w * right.z + x * right.y - y * right.x + z * right.w;
	rW = w * right.w - x * right.x - y * right.y - z * right.z;
	return Quaternion(rX, rY, rZ, rW);
}

Quaternion::~Quaternion()
{
}
