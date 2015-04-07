#include "Camera.h"
#include "glm\gtc\matrix_transform.hpp"


Camera::Camera(void)
{
	_position = vec3(0,0,5000);
	_target = vec3(0,0,0);
	_up = vec3(0,1,0);

	calcProjection();
	calcModel();
	calcView();
}

void Camera::calcProjection()
{
	_projection = perspective(45.0f, 1.0f, 0.01f, 100000.0f);	
}
void Camera::calcModel()
{
	_model = mat4(1.0f);
}
void Camera::calcView()
{
	_view = lookAt(_position, _target, _up);
}

void Camera::Update()
{
	calcView();
	MVP = _projection * _view * _model;
}

Camera::~Camera(void)
{
}
