#pragma once
#include "includes.h"
#include "Helpers.h"
#include "Texture.h"

using namespace glm;

class BaseObject
{
protected:
	string name;

	/* ������ ������ */
	GLfloat* _vertexList;
	GLfloat* _vertexListForCircuit;

	/* ������� ������� */
	GLuint vertexArrays;
	GLuint vertexbuffer;
	GLuint vertexbufferForCircuit;

	/* �������� */
	map<const char*, Texture*> _texture;

	/* ������ */
	GLuint shaderID;
	GLuint matrixID;
	GLuint textureID1;
protected:
	virtual void init()=0;
	virtual void initCircuit()=0;
	virtual void initShaders()=0;
	virtual void initGeometry()=0;
public:
	bool isEnable;
	BaseObject();

	void AddTexture(const char *textureFile, GLuint shaderTextureId);

	~BaseObject();
};

