#pragma once
#include "includes.h"
#include "Helpers.h"
#include "Texture.h"

class BaseObject
{
protected:
	string name;

	GLfloat* _vertexList;

	/* Индексы буферов */
	GLuint vertexArrays;
	GLuint vertexbuffer;

	map<const char*, Texture*> _texture;


	/* Шейдер */
	GLuint shaderID;
	GLuint matrixID;
	GLuint textureID1;
protected:
	virtual void init()=0;
	virtual void initShaders()=0;
	virtual void initGeometry()=0;
public:
	BaseObject();

	void AddTexture(const char *textureFile, GLuint shaderTextureId);

	~BaseObject();
};

