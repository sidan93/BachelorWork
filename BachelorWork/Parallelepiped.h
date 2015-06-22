#pragma once
#include "includes.h"
#include "Helpers.h"
#include "Texture.h"
#include "BaseObject.h"
#include "Section.h"

using namespace glm;

class Section;

class Parallelepiped : public BaseObject
{
protected:
	GLfloat* _mapcoordList;
	GLfloat* _normalList;

	GLuint uvbuffer;
	GLuint normalbuffer;

	GLuint shaderPosID;
	GLuint shaderSizeID;
	GLuint shaderSectionID;
	GLuint shaderSectionEnableID;
	GLuint shaderAlphaID;

	int _material;

	Section *section;
protected:
	virtual void init() override;
	virtual void initCircuit() override;
	virtual void initShaders() override;
	virtual void initGeometry() override;
public:

	// TODO so bad
	/* Позиционирование */
	vec3 position;
	vec3 size;
	vec3 GlobalSize;
	float alpha;

	Parallelepiped(vec3 position, vec3 size, int material);

	void Draw(float *MVP, int displayType);

	void setSectionLink(Section *section_);

	~Parallelepiped();
};

