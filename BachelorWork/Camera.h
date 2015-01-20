#pragma once
#include "glew.h"
#include "freeglut.h"
#include "Vector.h"
#include "Matrix.h"

class Camera
{
private:
	Matrix _world;
	Matrix _projection;
public:
	Camera(void);

	void Update();

	~Camera(void);
};

