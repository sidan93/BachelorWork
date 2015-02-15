#pragma once
#include "includes.h"
#include "Helpers.h"

class SkyBox
{
	GLuint texture;
public:
	SkyBox();
	SkyBox(const char * file);
	~SkyBox(void);
};

