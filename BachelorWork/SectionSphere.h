#pragma once
#include "includes.h"
#include "BaseObject.h"

using namespace glm;

typedef pair<float, vec3> Coloring;

class SectionSphere : public BaseObject
{
public:
	vec3 center;
	float radius;

	float minPower;
	float maxPower;
	vector<Coloring> coloring;
private:
	int pointCount;
protected:
	virtual void init() override;
	virtual void initCircuit() override;
	virtual void initShaders() override;
	virtual void initGeometry() override;
private:
	//bool SortColoring(Coloring first, Coloring second);
public:
	SectionSphere();
	vec3 getColor(vec3 target);
	void readColoring();
	void Draw(float *MVP);
	void Update();

	int getColoringCount() const;
	float* getColoring();
	~SectionSphere();
};

