#pragma once
#include "glew.h"
#include "freeglut.h"
#include "glm\gtx\euler_angles.hpp"

using namespace glm;

class Camera
{
public:
	mat4 MVP;
private:
	mat4 _projection;
	mat4 _view;
	mat4 _model;
	
	vec3 _target;
	vec3 _up;
public:
	vec3 _position;
public:
	Camera(void);

	void Update();

	~Camera(void);

private:
	void calcProjection();
	void calcView();
	void calcModel();
};

