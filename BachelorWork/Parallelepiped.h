#pragma once
#include "includes.h"
#include "Helpers.h"
#include "Texture.h"

using namespace glm;

class Parallelepiped
{
	string name;

	GLfloat* _vertexList;
	GLfloat* _mapcoordList;
	GLfloat* _normalList;

	/* Индексы буферов */
	GLuint vertexArrays;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	
	map<const char*, Texture*> _texture;

	/* Позиционирование */
	vec3 position;
	vec3 size;

	/* Шейдер */
	GLuint shaderID;
	GLuint shaderPosID;
	GLuint shaderSizeID;
	GLuint matrixID;
	GLuint textureID1;
private:
	void init();
	void initShaders();
	void initGeometry();
public:
	Parallelepiped(vec3 position, vec3 size);

	void AddTexture(const char *textureFile, GLuint shaderTextureId);

	void Draw(float *MVP, int displayType);

	~Parallelepiped();
};

