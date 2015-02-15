#pragma once
#include "includes.h"

using namespace std;

class Texture
{
private:
	GLuint Texture::loadTexture(const char *filename);
public:
	Texture();
	~Texture();
};

