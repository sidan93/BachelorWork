#pragma once
#include "BaseObject.h"
#include "includes.h"
#include "Parallelepiped.h"

using namespace glm;

class Parallelepiped;

class Section : public BaseObject
{
public:
	vec3 position;
	bool isEnableGridSection;
private:
	vec3 direction;
	vec3 maxSize;
	int step;

	int countPoint;

	float _getCubeSizeForShaders(vec3);
protected:
	virtual void init() override;
	virtual void initShaders() override;
	void initShadersSection();
	virtual void initGeometry() override;
	void initSectionGeomentry();
	virtual void initCircuit() override;

	// ��� ����� ������������ �� �������
	GLfloat* _vertexListSection;
	int countPointSection;
	GLuint vertexSectionbuffer;

	GLfloat* _vertexListSectionCenter;
	GLuint vertexSectionCenterbuffer;

	GLuint vertexCubeArrays;
	GLuint shaderCubeID;
	GLuint matrixCubeID;
public:
	Section();
	
	void Init();

	void Draw(float *MVP);
	void Update(vector<Parallelepiped*> lists);

	vec3 getPosition() const;
	void setMaxSize(vec3 size_);

	~Section();
};

