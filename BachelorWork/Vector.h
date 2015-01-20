#pragma once
class Vector
{
private:
	float _x;
	float _y;
	float _z;
	// Если w == 1, то это точка, если w == 0, то это верктор
	float _w;
public:
	Vector(void);
	Vector(float x, float y);
	Vector(float x, float y, float z);
	Vector(float x, float y, float z, float w);

	float& X();
	float& Y();
	float& Z();
	float& W();

	~Vector(void);
private:
	void init(float x, float y, float z, float w);
};

