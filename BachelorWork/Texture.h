#pragma once
#include "includes.h"

using namespace std;

class Texture
{
private:
	// Идентификатор текстуры
	GLuint _id;
	// Имя исходного файла
	const char *_filename;
	// Позиция в шейдере
	GLuint _shaderIndex;

	GLuint Texture::loadTexture();
public:
	Texture(const char *filename);
	Texture(const char *filename, GLuint shaderIndex);

	void BindTexture(GLuint shaderIndex, int textureNumber);
	void BindTexture(int textureNumber);
	
	~Texture();
};

