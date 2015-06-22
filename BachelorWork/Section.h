#pragma once
#include "BaseObject.h"
#include "includes.h"
#include "Parallelepiped.h"
#include "SectionSphere.h"

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

	GLuint vertexArrays1;

	int countPoint;
	int MAX_ITERATION_REC;

	// Сфера по которой проиходит распределение
	SectionSphere *sectionSphere;

	float _getCubeSizeForShaders(vec3);
protected:
	virtual void init() override;
	virtual void initShaders() override;
	void initShadersSection();
	virtual void initGeometry() override;
	void initSectionGeomentry();
	virtual void initCircuit() override;

	// Для фигур получившихся от сечения
	GLfloat* _vertexListSection;
	int countPointSection;
	GLuint vertexSectionbuffer;

	GLfloat* _vertexListSectionColor;
	GLuint vertexSectionColorbuffer;

	GLfloat* _vertexListCurcuitColor;
	int countPointForCurcuit;
	GLuint vertexCurcuitColorbuffer;

	GLuint vertexCubeArrays;
	GLuint shaderCubeID;
	GLuint matrixCubeID;
public:
	Section(SectionSphere *sectionSphere_);
	
	void Init();

	void Draw(float *MVP);
	void Update(vector<Parallelepiped*> lists);

	vec3 getPosition() const;
	void setMaxSize(vec3 size_);

	~Section();

private:
	void _UpdateTopRec(float leftX, float rightX, float leftZ, float rightZ, float centerX, float centerZ);
	void _UpdateLeftRec(float leftX, float rightX, float leftZ, float rightZ, float centerX, float centerZ);
	void _UpdateDepRec(float leftX, float rightX, float leftY, float rightZ, float centerX, float centerY);
	void _recursive(float leftU, float rightU, float leftV, float rightV, int type, int n);
};

