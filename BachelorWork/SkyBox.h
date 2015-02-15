#pragma once
#include <string>
#include "glm/glm.hpp"
#include <io.h>
#include "GL/glew.h"
#include "Helpers.h"
#include <memory>
#include "glm/glm.hpp"

class SkyBox
{
	GLuint texture;
public:
	SkyBox();
	SkyBox(const char * file);
	~SkyBox(void);
};

